import asyncio
import serial_asyncio
import struct
from serial.serialutil import SerialException
import logging
import MRAS_pb2

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

    def __init__(self, port: str, baudrate: int):
        self.port = port
        self.baudrate = baudrate
        self.logger = logging.getLogger(self.__class__.__name__)

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
                text_msg = MRAS_pb2.ProtobufTextLogMsg()
                text_msg.ParseFromString(data)
                print(text_msg.text)
            except (ConnectionResetError, SerialException):
                self.logger.info(f"Connection lost on port {self.port}")
                self.connected = False

                # try to reconnect if connection was lost
                asyncio.create_task(self.connect())


loop = asyncio.get_event_loop_policy().get_event_loop()
serial_input = SerialLineInput("COM13", 115200)
loop.create_task(serial_input.connect())
try:
    # run the loop forever
    loop.run_forever()
except KeyboardInterrupt:  # hide KeyboardInterrupt error
    print("Stopping...")
