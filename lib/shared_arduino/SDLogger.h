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
    using Subsystem::Subsystem;
private:
    SUBSYSTEM_NAME("SDLogger")

    int8_t setup() override;

    int8_t loop() override;

    SUBSYSTEM_NO_MESSAGE_HANDLER
    File log_file;
};


#endif //MRAS_SDLOGGER_H
