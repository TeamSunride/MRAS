//
// Created by Tom Danvers on 10/02/2023.
//

#ifndef MRAS_GROUNDSDLOGGER_H
#define MRAS_GROUNDSDLOGGER_H


#include "SDLogger.h"

class GroundSDLogger : public SDLogger {
    using SDLogger::SDLogger;

    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

    uint32_t last_log_entry = millis();

    struct GroundDataLogPayload {
        float latitude = 0;
        float longitude = 0;
        float altitude = 0;
        uint8_t fix_type = 0;
        uint8_t SIV = 0;
    } data;
};


#endif //MRAS_GROUNDSDLOGGER_H
