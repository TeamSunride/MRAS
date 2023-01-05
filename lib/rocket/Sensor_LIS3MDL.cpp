//
// Created by Tom Danvers on 17/12/2022.
//

#include "Sensor_LIS3MDL.h"

int8_t Sensor_LIS3MDL::setup() {
    log("Startup...");
    lis->begin();
    log("Startup complete");
    log("Loading default configuration");
    lis->default_configuration();
//    if (error == 0) {
//        log("Default configuration loaded");
//    } else {
//        log("Error loading default configuration");
//        return (int8_t) error;
//    }

    // TODO: add error codes for default configuration

    log("Loaded default configuration");

    return 0;
}

int8_t Sensor_LIS3MDL::loop() {
    auto *mag_msg = new MagnetometerDataMsg();

    mag_msg->mag = (Vector<float, 3>) lis->get_mag();

    publish(mag_msg);

    return 0;
}
