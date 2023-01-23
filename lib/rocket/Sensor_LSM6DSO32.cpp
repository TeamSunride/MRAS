//
// Created by Tom Danvers on 17/12/2022.
//

#include "Sensor_LSM6DSO32.h"

int8_t Sensor_LSM6DSO32::setup() {
    log("Startup...");
    lsm->begin();
    log("Startup complete");
    log("Loading default configuration");
    uint8_t error = lsm->default_configuration();

    // TODO: add error codes for default configuration

    if (error == 0) {
        log("Default configuration loaded");
    } else {
        log("Error loading default configuration");
        return (int8_t) error;
    }

    return 0;
}

int8_t Sensor_LSM6DSO32::loop() {

    auto *accel_msg = new AccelerometerDataMsg(AccelerometerDataMsg_t);
    auto *gyro_msg = new GyroDataMsg();

    accel_msg->acceleration = (Vector<float, 3>) lsm->get_accel();
    gyro_msg->gyro = (Vector<float, 3>) lsm->get_gyro();

    publish(accel_msg);
    publish(gyro_msg);

    return 0;
}
