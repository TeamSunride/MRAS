//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_FAKEACCELEROMETER_H
#define MRAS_FAKEACCELEROMETER_H


#include "Subsystem.h"

class FakeAccelerometer : public Subsystem {
public:
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;

    void on_message(SystemMessage *msg) override {} // do nothing

    const char* get_name() override {
        return "FakeAccelerometer";
    }
};


#endif //MRAS_FAKEACCELEROMETER_H
