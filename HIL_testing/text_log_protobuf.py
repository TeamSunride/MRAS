import asyncio
from time import time

import serial_asyncio
import struct
from serial.serialutil import SerialException
import logging
import MRAS_pb2
from google.protobuf import text_format
from google.protobuf.message import DecodeError
from collections import deque
from typing import Deque, List

import sys
import asyncio
from qasync import QEventLoop
from PyQt5 import QtCore, QtWidgets
import pyqtgraph as pg
from pyqtgraph import PlotItem, PlotWidget, PlotDataItem, GraphicsLayoutWidget

# configure the logging module to output the "INFO" log level
logging.basicConfig(level=logging.INFO)


class SerialLineInput:
    """
    Object that connects to a serial port, and calls a list of outputs when a line is read
    """

    # see the Streams documentation for information about these APIs
    # https://docs.python.org/3/library/asyncio-stream.html
    reader: asyncio.StreamReader
    writer: asyncio.StreamWriter

    port: str
    baudrate: int
    connected: bool = False
    logger: logging.Logger

    subscribers: List

    def __init__(self, port: str, baudrate: int):
        self.port = port
        self.baudrate = baudrate
        self.logger = logging.getLogger(self.__class__.__name__)
        self.subscribers = []

    def add_subscriber(self, subscriber):
        self.subscribers.append(subscriber)

    async def connect(self):
        while not self.connected:
            self.logger.info(f"Attempting to open Serial connection on port {self.port}")
            try:
                # open a serial connection to our Arduino
                self.reader, self.writer = await serial_asyncio.open_serial_connection(
                    url=self.port, baudrate=self.baudrate
                )
            except (ConnectionRefusedError, SerialException) as e:
                self.logger.info(e)
                self.logger.info(f"Connection refused on port {self.port}, retrying in 5 seconds...")
                await asyncio.sleep(5)
            else:
                self.logger.info(f"Successfully opened Serial connection on port {self.port}")
                self.connected = True

        asyncio.create_task(self.listen())

    async def listen(self):
        while self.connected:
            try:
                # read a line of data from the serial port
                size_data = await self.reader.readexactly(2)
                size = struct.unpack("<H", size_data)[0]
                data = await self.reader.read(size)
                msg = MRAS_pb2.MRASProtobufMsg()
                msg.ParseFromString(data)
                which_message = msg.WhichOneof("message")
                if which_message is None:
                    continue
                msg = getattr(msg, which_message)
                if which_message == "text_log":
                    print(msg.text)
                    pass
                else:
                    pass
                    # msg_string = text_format.MessageToString(msg, as_one_line=True, print_unknown_fields=True)
                    # print(f"{which_message}<{msg_string}>")

                for subscriber in self.subscribers:
                    subscriber(msg, which_message)

            except (ConnectionResetError, SerialException):
                self.logger.info(f"Connection lost on port {self.port}")
                self.connected = False

                # try to reconnect if connection was lost
                asyncio.create_task(self.connect())
            except DecodeError:
                pass


class TimeSeries:
    buffer: Deque
    curve: PlotDataItem
    n = 0

    def __init__(self, num_samples, plot_item: PlotItem, *args, **kwargs):
        self.buffer = deque([0]*num_samples, maxlen=num_samples)
        self.curve: PlotDataItem = plot_item.plot(*args, **kwargs)
        self.curve.setData(self.buffer)
        self.timer = QtCore.QTimer()
        self.timer.timeout.connect(self.redraw)
        self.timer.start(50)

    def update(self, new_sample):
        self.buffer.append(new_sample)

    def redraw(self):
        self.curve.setData(self.buffer)


class DataDashboard:
    win: GraphicsLayoutWidget

    samples = 5000

    def __init__(self):
        self.win = pg.GraphicsLayoutWidget(show=True, title="MRAS Data Dashboard")
        self.win.setAntialiasing(False)
        accel_plot_item: PlotItem = self.win.addPlot(title="Low-G Accelerometer")
        accel_plot_item.setDownsampling(mode="subsample", auto=True)
        accel_plot_item.showGrid(x=True, y=True)
        self.accel_x = TimeSeries(self.samples, accel_plot_item, pen=pg.mkPen("r", width=2))
        self.accel_y = TimeSeries(self.samples, accel_plot_item, pen="g")
        self.accel_z = TimeSeries(self.samples, accel_plot_item, pen="b")

        high_g_accel_plot_item = self.win.addPlot(title="High-G Accelerometer")
        high_g_accel_plot_item.setDownsampling(mode="subsample", auto=True)
        high_g_accel_plot_item.showGrid(x=True, y=True)
        self.high_g_accel_x = TimeSeries(self.samples, high_g_accel_plot_item, pen="r")
        self.high_g_accel_y = TimeSeries(self.samples, high_g_accel_plot_item, pen="g")
        self.high_g_accel_z = TimeSeries(self.samples, high_g_accel_plot_item, pen="b")

        mag_plot_item = self.win.addPlot(title="Magnetometer")
        mag_plot_item.setDownsampling(mode="subsample", auto=True)
        mag_plot_item.showGrid(x=True, y=True)
        self.mag_x = TimeSeries(self.samples, mag_plot_item, pen="r")
        self.mag_y = TimeSeries(self.samples, mag_plot_item, pen="g")
        self.mag_z = TimeSeries(self.samples, mag_plot_item, pen="b")

        self.win.nextRow()

        pressure_plot_item = self.win.addPlot(title="Pressure")
        pressure_plot_item.setDownsampling(mode="subsample", auto=True)
        pressure_plot_item.showGrid(x=True, y=True)
        self.pressure = TimeSeries(100, pressure_plot_item, pen="r")

        temp_plot_item = self.win.addPlot(title="Temperature")
        temp_plot_item.setDownsampling(mode="subsample", auto=True)
        temp_plot_item.showGrid(x=True, y=True)
        self.temp = TimeSeries(100, temp_plot_item, pen="r")

    def on_msg(self, msg, which_message):
        if which_message == "accelerometer_data":
            if msg.type == MRAS_pb2.AccelerometerType.LOW_G:
                self.accel_x.update(msg.x)
                self.accel_y.update(msg.y)
                self.accel_z.update(msg.z)
            elif msg.type == MRAS_pb2.AccelerometerType.HIGH_G:
                self.high_g_accel_x.update(msg.x)
                self.high_g_accel_y.update(msg.y)
                self.high_g_accel_z.update(msg.z)
        elif which_message == "magnetometer_data":
            self.mag_x.update(msg.x)
            self.mag_y.update(msg.y)
            self.mag_z.update(msg.z)
        elif which_message == "barometer_data":
            self.pressure.update(msg.pressure)
            self.temp.update(msg.temperature)


dashboard = DataDashboard()

app = QtWidgets.QApplication(sys.argv)
loop = QEventLoop(app)
asyncio.set_event_loop(loop)

serial_input = SerialLineInput("COM13", 115200)
serial_input.add_subscriber(dashboard.on_msg)
loop.create_task(serial_input.connect())

try:
    # run the loop forever
    loop.run_forever()
except KeyboardInterrupt:  # hide KeyboardInterrupt error
    print("Stopping...")
