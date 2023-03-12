//
// Created by Tom Danvers on 10/02/2023.
//

#ifndef MRAS_GROUNDSDLOGGER_H
#define MRAS_GROUNDSDLOGGER_H


#include "SDLogger.h"
#include "system_messages/RadioStatusMsg.h"

/**
 * Data logger for the ground station, uses the SD card to log CSV data and text logs to the same file.
 */
class GroundSDLogger : public SDLogger {
    using SDLogger::SDLogger;

    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

    uint32_t last_log_entry = millis();

    /**
     * @brief The data to be logged
     *
     * The data is logged as a CSV file with the following columns:
     * latitude, longitude, altitude, fix_type, SIV
     */
    struct GroundDataLogPayload {
        float latitude = 0;
        float longitude = 0;
        float altitude = 0;
        uint8_t fix_type = 0;
        uint8_t SIV = 0;
    } data;

    RadioStatusMsg radio_status = {};
};


#endif //MRAS_GROUNDSDLOGGER_H
