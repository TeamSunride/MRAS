//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_FAKEACCELEROMETER_H
#define MRAS_FAKEACCELEROMETER_H


#include "Subsystem.h"

/**
 * @brief A fake accelerometer for testing
 *
 * This class is a fake accelerometer that can be used for testing
 * It will send an AccelerometerDataMsg to the system every time its `loop()` method is called
 */
class FakeAccelerometer : public Subsystem {
public:
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;

    SUBSYSTEM_NO_MESSAGE_HANDLER
    SUBSYSTEM_NAME("FakeAccelerometer")
};


#endif //MRAS_FAKEACCELEROMETER_H
