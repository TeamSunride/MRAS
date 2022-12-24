//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_ARDUINODATALOGGER_H
#define MRAS_ARDUINODATALOGGER_H


#include "Subsystem.h"
#include "Arduino.h"

class ArduinoDataLogger: public Subsystem {
public:
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

    SUBSYSTEM_NAME("ArduinoDataLogger")
};


#endif //MRAS_ARDUINODATALOGGER_H
