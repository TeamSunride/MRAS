//
// Created by Tom Danvers on 18/12/2022.
//

#include "Sensor_ADXL375.h"
#include "system_messages/AccelerometerDataMsg.h"

int8_t Sensor_ADXL375::setup() {
    log("Startup...");
    adxl->begin();
    log("Loading default configuration");
    uint8_t error = adxl->default_configuration();

    if (error == 0) {
        log("Default configuration loaded");
    } else {
        log("Error loading default configuration");
        return (int8_t) error;
    }

    return 0;
}

int8_t Sensor_ADXL375::loop() {
    auto *accel_msg = new AccelerometerDataMsg(HighGAccelerometerDataMsg_t);
    accel_msg->acceleration = (Vector<float, 3>) adxl->get_accel();
    publish(accel_msg);
    return 0;
}
