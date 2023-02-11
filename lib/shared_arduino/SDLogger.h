//
// Created by Tom Danvers on 08/02/2023.
//

#ifndef MRAS_SDLOGGER_H
#define MRAS_SDLOGGER_H


#include "Subsystem.h"
#include "Arduino.h"
#include "SD.h"

class SDLogger : public Subsystem {
public:
    SDLogger(uint8_t id, uint8_t sdPin) : Subsystem(id) {
        SD_pin = sdPin;
    }
private:
    uint8_t SD_pin;

    SUBSYSTEM_NAME("SDLogger")

    int8_t setup() override;

protected:
    File log_file;
    bool setup_complete = false;
};


#endif //MRAS_SDLOGGER_H
