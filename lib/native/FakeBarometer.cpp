#include "FakeBarometer.h"
#include "system_messages/BarometerDataMsg.h"

int8_t FakeBarometer::setup() {
    log("Starting up");
    return 0;
}

int8_t FakeBarometer::loop() {
    log("Generating fake data");
    auto *msg = new BarometerDataMsg();
    msg->pressure = 101375;
    msg->temperature = 15;

    publish(msg);
    return 0;
}
