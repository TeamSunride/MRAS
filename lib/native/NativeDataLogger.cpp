//
// Created by Tom Danvers on 17/12/2022.
//

#include "NativeDataLogger.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/MagnetometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/GNSSDataMsg.h"
#include "system_messages/TelemetryMessageReceivedMsg.h"
#include "telemetry_messages/TelemetryDataMsg.h"

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
            auto mag_msg = (MagnetometerDataMsg *) msg;
            log("MagnetometerDataMsg: %f %f %f",
                mag_msg->mag[0],
                mag_msg->mag[1],
                mag_msg->mag[2]);
            break;
        }
        case BarometerDataMsg_t: {
            auto baro_msg = (BarometerDataMsg *) msg;
            log("BarometerDataMsg: Pressure: %f Temperature: %f", baro_msg->pressure, baro_msg->temperature);
            break;
        }
        case GNSSDataMsg_t: {
            auto gnss_msg = (GNSSDataMsg *) msg;
            log("GNSSDataMsg: Lat: %f  Lon: %f  Alt: %f  Fix: %d  SIV: %d",
                gnss_msg->latitude,
                gnss_msg->longitude,
                gnss_msg->altitude,
                gnss_msg->fix_type,
                gnss_msg->SIV);
            break;
        }
        case ReceivedTelemetryMessageMsg_t: {
            auto system_message = (TelemetryMessageReceivedMsg *) msg;
            TelemetryMessage *telemetry_message = system_message->telemetry_message;
            switch (telemetry_message->get_type()) {
                case TelemetryDataMsg_t: {
                    auto data_msg = (TelemetryDataMsg*) telemetry_message;
                    char buffer[255];
                    data_msg->to_csv(buffer, sizeof buffer);
                    log("TelemetryDataMsg: %s", buffer);
                    break;
                }
            }
            break;
        }
        default:
            break;
    }
}
