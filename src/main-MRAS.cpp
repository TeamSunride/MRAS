//
// Created by Tom Danvers on 05/12/2022.
//

#include <cstdio>

#include "MRAS_System.h"
#include "ArduinoTextLogger.h"
#include "NativeDataLogger.h"
#include "Sensor_LSM6DSO32.h"
#include "Arduino.h"
#include "Sensor_LIS3MDL.h"
#include "Sensor_MS5607.h"

TextLogger* logger = new ArduinoTextLogger(0, 115200);
MRAS_System* mras = MRAS_System::get_instance();

auto *data_logger = new NativeDataLogger(1);

auto *accelerometer = new Sensor_LSM6DSO32(2, 40, SPI, 5e6);
auto *magnetometer = new Sensor_LIS3MDL(3, 37, SPI, 5e6);
auto *barometer = new Sensor_MS5607(4, 0x76, &Wire2);

void setup() {
    mras->set_logger(logger);

    mras->add_subsystem(magnetometer);
    mras->add_subsystem(accelerometer);
    mras->add_subsystem(barometer);

    accelerometer->add_subscriber(data_logger);
    magnetometer->add_subscriber(data_logger);
    barometer->add_subscriber(data_logger);

    mras->setup();
}

void loop() {
    mras->loop();
    delay(1000);
}