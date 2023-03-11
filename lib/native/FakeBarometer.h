
#ifndef MRAS_FAKEBAROMETER_H
#define MRAS_FAKEBAROMETER_H


#include "Subsystem.h"

class FakeBarometer : public Subsystem {
public:
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;

    SUBSYSTEM_NO_MESSAGE_HANDLER
    SUBSYSTEM_NAME("FakeBarometer")
};


#endif //MRAS_FAKEBAROMETER_H