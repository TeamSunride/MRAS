//
// Created by Tom Danvers on 17/12/2022.
//

#include "FakeAccelerometer.h"
#include "system_messages/AccelerometerDataMsg.h"

int8_t FakeAccelerometer::setup() {
    log("Starting up");
    return 0;
}

int8_t FakeAccelerometer::loop() {
    log("Generating fake data");
    auto *msg = new AccelerometerDataMsg();
    msg->acceleration = {0, 1, 0};
    msg->timestamp = 1234567;

    publish(msg);
    return 0;
}
