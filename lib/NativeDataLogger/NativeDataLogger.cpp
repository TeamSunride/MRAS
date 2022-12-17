//
// Created by Tom Danvers on 17/12/2022.
//

#include "NativeDataLogger.h"
#include "system_messages/AccelerometerDataMsg.h"

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
            log("AccelerometerDataMsg: %f %f %f", accel_msg->acceleration[0], accel_msg->acceleration[1],
                accel_msg->acceleration[2]);
            break;
        }
        default:
            break;
    }
}
