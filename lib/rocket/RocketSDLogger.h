//
// Created by Tom Danvers on 10/02/2023.
//

#ifndef MRAS_ROCKETSDLOGGER_H
#define MRAS_ROCKETSDLOGGER_H


#include "SDLogger.h"
#include "system_messages/TextLogMsg.h"
#include "Vector.h"
#include <string>

/**
 * @brief Data logger for the rocket, uses the Teensy SD card to log CSV data and text logs to the same file.
 */
class RocketSDLogger : public SDLogger {
    using SDLogger::SDLogger;

    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

    uint32_t last_log_entry = millis();
    uint32_t last_flush = millis();

    /**
     * @brief The data to be logged
     *
     * The data is logged as a CSV file with the following columns:
     * accel_x, accel_y, accel_z, accel_high_G_x, accel_high_G_y, accel_high_G_z, gyro_x, gyro_y, gyro_z, mag_x, mag_y,
     * mag_z, pressure, temperature, latitude, longitude, altitude, fix_type, SIV
     */
    struct RocketDataLogPayload {
        Vector<float, 3> accel = {};
        Vector<float, 3> accel_high_G = {};
        Vector<float, 3> gyro = {};
        Vector<float, 3> mag = {};
        float pressure = 0;
        float temperature = 0;
        float latitude = 0;
        float longitude = 0;
        float altitude = 0;
        uint8_t fix_type = 0;
        uint8_t SIV = 0;
        float altitude_estimate = 0;
        float velocity_estimate = 0;
        char last_event[16] = "INIT";
        char phase[16] = "INIT";
    } data;
};


#endif //MRAS_ROCKETSDLOGGER_H
