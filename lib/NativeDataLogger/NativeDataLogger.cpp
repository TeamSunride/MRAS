//
// Created by Tom Danvers on 17/12/2022.
//

#include "NativeDataLogger.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/MagnetometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"

int8_t NativeDataLogger::setup() {
    return 0;
}

int8_t NativeDataLogger::loop() {
    return 0;
}

void NativeDataLogger::on_message(SystemMessage *msg) {
    switch (msg->get_type()) {
        case AccelerometerDataMsg_t: {
            auto accel_msg = (AccelerometerDataMsg *) msg;
            log("AccelerometerDataMsg: %f %f %f",
                accel_msg->acceleration[0],
                accel_msg->acceleration[1],
                accel_msg->acceleration[2]);
            break;
        }
        case HighGAccelerometerDataMsg_t: {
            auto accel_msg = (AccelerometerDataMsg *) msg;
            log("HighGAccelerometerDataMsg_t: %f %f %f",
                accel_msg->acceleration[0],
                accel_msg->acceleration[1],
                accel_msg->acceleration[2]);
            break;
        }
        case MagnetometerDataMsg_t: {
            auto mag_msg = (MagnetometerDataMsg*) msg;
            log("MagnetometerDataMsg: %f %f %f",
                mag_msg->mag[0],
                mag_msg->mag[1],
                mag_msg->mag[2]);
            break;
        }
        case BarometerDataMsg_t: {
            auto baro_msg = (BarometerDataMsg*) msg;
            log("BarometerDataMsg: Pressure: %f Temperature: %f", baro_msg->pressure, baro_msg->temperature);
            break;
        }
        default:
            break;
    }
}
