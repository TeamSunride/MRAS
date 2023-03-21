//
// Created by Nikilesh -- 8/3/2023
//

#include <cstdio>

#include "MRAS_System.h"
#include "MRAS_Config.h"
#include "ArduinoTextLogger.h"
#include "NativeDataLogger.h"
#include "Sensor_LSM6DSO32.h"
#include "Arduino.h"
#include "Sensor_LIS3MDL.h"
#include "Sensor_MS5607.h"
#include "Sensor_ADXL375.h"
#include "Sensor_ZOEM8Q.h"
#include "RocketTelemetrySystem.h"
#include "StateEstimator.h"
#include "RocketSDLogger.h"
#include "SimulinkDataLogger.h"
#include "ArduinoBuzzer.h"

auto logger = ArduinoTextLogger(0, 0);
MRAS_System *mras = MRAS_System::get_instance();

NativeDataLogger data_logger = NativeDataLogger(1);

Sensor_LSM6DSO32 imu = Sensor_LSM6DSO32(2, MRAS_LSM6DSO32_CHIP_SELECT, MRAS_LSM6DSO32_SPI_BUS,
                                        MRAS_LSM6DSO32_SPI_FREQUENCY);

Sensor_MS5607 barometer = Sensor_MS5607(4, MRAS_MS5607_I2C_ADDRESS, MRAS_MS5607_I2C_BUS, MRAS_MS5607_I2C_FREQUENCY);



StateEstimator altitudeEstimator = StateEstimator(8, 0.05);



SimulinkDataLogger sim_logger = SimulinkDataLogger(10);

ArduinoBuzzer buzzer = ArduinoBuzzer(10, 10);

void setup() {
    mras->set_logger(&logger);
    mras->set_buzzer(&buzzer);

    mras->add_subsystem(&altitudeEstimator);
    mras->add_subsystem(&sim_logger);
    altitudeEstimator.add_subscriber(&sim_logger);
    sim_logger.add_subscriber(&altitudeEstimator);


    mras->setup();
}

void loop() {
    mras->loop();
    delay(0);

}