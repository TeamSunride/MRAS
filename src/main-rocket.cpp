//
// Created by Tom Danvers on 05/12/2022.
//

#include <cstdio>
#include "timestamp.h"
#include "MRAS_System.h"
#include "MRAS_Config.h"
#include "ArduinoTextLogger.h"
#include "Sensor_LSM6DSO32.h"
#include "Arduino.h"
#include "Sensor_LIS3MDL.h"
#include "Sensor_MS5607.h"
#include "Sensor_ADXL375.h"
#include "Sensor_MAX_M10S.h"
//#include "Sensor_SAM_M10Q.h"
#include "RocketTelemetrySystem.h"
#include "RocketSDLogger.h"
#include "ArduinoBuzzer.h"
#include "StateEstimator.h"
#include "LEDSubsystem.h"

auto logger = ArduinoTextLogger(0, 0);
MRAS_System *mras = MRAS_System::get_instance();

Sensor_LSM6DSO32 imu = Sensor_LSM6DSO32(2, MRAS_LSM6DSO32_CHIP_SELECT, MRAS_LSM6DSO32_SPI_BUS,
                                        MRAS_LSM6DSO32_SPI_FREQUENCY);
Sensor_LIS3MDL magnetometer = Sensor_LIS3MDL(3, MRAS_LIS3MDL_CHIP_SELECT, MRAS_LIS3MDL_SPI_BUS,
                                             MRAS_LIS3MDL_SPI_FREQUENCY);
Sensor_MS5607 barometer = Sensor_MS5607(4, MRAS_MS5607_I2C_ADDRESS, MRAS_MS5607_I2C_BUS,
                                        MRAS_MS5607_I2C_FREQUENCY);
Sensor_ADXL375 accelerometer = Sensor_ADXL375(5, MRAS_ADXL375_CHIP_SELECT, MRAS_ADXL375_SPI_BUS,
                                              MRAS_ADXL375_SPI_FREQUENCY);
Sensor_MAX_M10S MAXM10s = Sensor_MAX_M10S(MAXM10s_ID, MRAS_MAX_M10S_GNSS_I2C_BUS, MRAS_MAX_M10S_GNSS_I2C_FREQUENCY, 5, "MAX-M10S");

#ifdef BUILD_ENV_kalpha
Sensor_MAX_M10S SAMM10q = Sensor_MAX_M10S(SAMM10Q_ID, MRAS_SAM_M10Q_GNSS_I2C_BUS, MRAS_SAM_M10Q_GNSS_I2C_FREQUENCY, 5, "SAM-M10Q");
#endif

RocketTelemetrySystem telemetry_system = RocketTelemetrySystem(8);

RocketSDLogger sd_logger = RocketSDLogger(9, BUILTIN_SDCARD);

StateEstimator altitudeEstimator = StateEstimator(10, 0.001);

ArduinoBuzzer buzzer = ArduinoBuzzer(11, BUZZER_PIN);

LEDSubsystem leds = LEDSubsystem(12, 0, 2);

void setup() {
    setSyncProvider(getTeensy3Time);

    // these must be added first
    mras->set_logger(&logger);
    mras->set_buzzer(&buzzer);
    mras->add_subsystem(&leds);

    mras->add_subsystem(&sd_logger);
    mras->add_subsystem(&magnetometer);
    mras->add_subsystem(&imu);
    mras->add_subsystem(&MAXM10s);
    mras->add_subsystem(&barometer);
    mras->add_subsystem(&accelerometer);
    mras->add_subsystem(&telemetry_system);
    mras->add_subsystem(&altitudeEstimator);
#ifdef BUILD_ENV_kalpha
    mras->add_subsystem(&SAMM10q);
    SAMM10q.add_subscriber(&sd_logger);
    SAMM10q.add_subscriber(&telemetry_system);
    SAMM10q.add_subscriber(&leds);
#endif

    imu.add_subscriber(&altitudeEstimator);
    barometer.add_subscriber(&altitudeEstimator);


    logger.add_subscriber(&sd_logger);
    imu.add_subscriber(&sd_logger);
    magnetometer.add_subscriber(&sd_logger);
    barometer.add_subscriber(&sd_logger);
    accelerometer.add_subscriber(&sd_logger);
    MAXM10s.add_subscriber(&sd_logger);
    altitudeEstimator.add_subscriber(&sd_logger);

    MAXM10s.add_subscriber(&telemetry_system);
    MAXM10s.add_subscriber(&leds);
    imu.add_subscriber(&telemetry_system);
    barometer.add_subscriber(&telemetry_system);
    altitudeEstimator.add_subscriber(&telemetry_system);

    mras->setup();
}

void loop() {
    mras->loop();
    //Serial.println(millis());
}