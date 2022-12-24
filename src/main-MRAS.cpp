//
// Created by Tom Danvers on 05/12/2022.
//

#include <cstdio>

#include "MRAS_System.h"
#include "ArduinoTextLogger.h"
#include "ArduinoDataLogger.h"
#include "Sensor_LSM6DSO32.h"
#include "Arduino.h"
#include "Sensor_LIS3MDL.h"
#include "Sensor_MS5607.h"
#include "Sensor_ADXL375.h"
#include "Sensor_ZOEM8Q.h"

auto logger = ArduinoTextLogger(0, 115200);
MRAS_System* mras = MRAS_System::get_instance();

ArduinoDataLogger data_logger = ArduinoDataLogger(1);

Sensor_LSM6DSO32 imu = Sensor_LSM6DSO32(2, 40, SPI, 5e6);
Sensor_LIS3MDL magnetometer = Sensor_LIS3MDL(3, 37, SPI, 5e6);
Sensor_MS5607 barometer = Sensor_MS5607(4, 0x76, &Wire2);
Sensor_ADXL375 accelerometer = Sensor_ADXL375(5, 3, SPI, 5e6);
Sensor_ZOEM8Q gnss = Sensor_ZOEM8Q(6, Wire2, 400000);

void setup() {
    mras->set_logger(&logger);

    mras->add_subsystem(&data_logger);
    mras->add_subsystem(&magnetometer);
    mras->add_subsystem(&imu);
    mras->add_subsystem(&barometer);
    mras->add_subsystem(&accelerometer);
    mras->add_subsystem(&gnss);

    imu.add_subscriber(&data_logger);
    magnetometer.add_subscriber(&data_logger);
    barometer.add_subscriber(&data_logger);
    accelerometer.add_subscriber(&data_logger);
    gnss.add_subscriber(&data_logger);

    mras->setup();
}

void loop() {
    mras->loop();
    delay(100);
}