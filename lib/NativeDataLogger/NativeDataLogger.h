//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_NATIVEDATALOGGER_H
#define MRAS_NATIVEDATALOGGER_H


#include "Subsystem.h"

class NativeDataLogger: public Subsystem {
public:
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

    const char* get_name() override {
        return "NativeDataLogger";
    }
};


#endif //MRAS_NATIVEDATALOGGER_H
