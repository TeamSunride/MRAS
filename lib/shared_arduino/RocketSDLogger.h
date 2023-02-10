//
// Created by Tom Danvers on 10/02/2023.
//

#ifndef MRAS_ROCKETSDLOGGER_H
#define MRAS_ROCKETSDLOGGER_H


#include "SDLogger.h"
#include "system_messages/TextLogMsg.h"
#include "Vector.h"

class RocketSDLogger : public SDLogger {
    using SDLogger::SDLogger;

    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

    uint32_t last_log_entry = millis();

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
    } data;
};


#endif //MRAS_ROCKETSDLOGGER_H
