//
// Created by Tom Danvers on 17/12/2022.
//

#include "ArduinoDataLogger.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/MagnetometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/GNSSDataMsg.h"
#include "MRAS.pb.h"
#include "protobuf_util.h"
#include <pb_encode.h>

int8_t ArduinoDataLogger::setup() {
    return 0;
}

int8_t ArduinoDataLogger::loop() {
    return 0;
}

void ArduinoDataLogger::on_message(SystemMessage *msg) {
    uint8_t protobuf_outbuffer[255];
    switch (msg->get_type()) {
        case AccelerometerDataMsg_t: {
            auto accel_msg = (AccelerometerDataMsg *) msg;
//            log("AccelerometerDataMsg: %f %f %f",
//                accel_msg->acceleration[0],
//                accel_msg->acceleration[1],
//                accel_msg->acceleration[2]);

            MRASProtobufMsg protobufMsg = MRASProtobufMsg_init_default;
            protobufMsg.which_message = MRASProtobufMsg_accelerometer_data_tag;
            protobufMsg.message.accelerometer_data = ProtobufAccelerometerDataMsg_init_zero;
            protobufMsg.message.accelerometer_data.x = accel_msg->acceleration[0];
            protobufMsg.message.accelerometer_data.y = accel_msg->acceleration[1];
            protobufMsg.message.accelerometer_data.z = accel_msg->acceleration[2];
            protobufMsg.message.accelerometer_data.type = AccelerometerType_LOW_G;
            send_protobuf_serial(protobuf_outbuffer,
                                 sizeof(protobuf_outbuffer),
                                 &protobufMsg,
                                 MRASProtobufMsg_fields);
            break;
        }
        case HighGAccelerometerDataMsg_t: {
            auto accel_msg = (AccelerometerDataMsg *) msg;
//            log("HighGAccelerometerDataMsg_t: %f %f %f",
//                accel_msg->acceleration[0],
//                accel_msg->acceleration[1],
//                accel_msg->acceleration[2]);

            MRASProtobufMsg protobufMsg = MRASProtobufMsg_init_default;
            protobufMsg.which_message = MRASProtobufMsg_accelerometer_data_tag;
            protobufMsg.message.accelerometer_data = ProtobufAccelerometerDataMsg_init_zero;
            protobufMsg.message.accelerometer_data.x = accel_msg->acceleration[0];
            protobufMsg.message.accelerometer_data.y = accel_msg->acceleration[1];
            protobufMsg.message.accelerometer_data.z = accel_msg->acceleration[2];
            protobufMsg.message.accelerometer_data.type = AccelerometerType_HIGH_G;
            send_protobuf_serial(protobuf_outbuffer,
                                 sizeof(protobuf_outbuffer),
                                 &protobufMsg,
                                 MRASProtobufMsg_fields);
            break;
        }
        case MagnetometerDataMsg_t: {
            auto mag_msg = (MagnetometerDataMsg*) msg;
//            log("MagnetometerDataMsg: %f %f %f",
//                mag_msg->mag[0],
//                mag_msg->mag[1],
//                mag_msg->mag[2]);

            MRASProtobufMsg protobufMsg = MRASProtobufMsg_init_default;
            protobufMsg.which_message = MRASProtobufMsg_magnetometer_data_tag;
            protobufMsg.message.magnetometer_data.x = mag_msg->mag[0];
            protobufMsg.message.magnetometer_data.y = mag_msg->mag[1];
            protobufMsg.message.magnetometer_data.z = mag_msg->mag[2];
            send_protobuf_serial(protobuf_outbuffer,
                                 sizeof(protobuf_outbuffer),
                                 &protobufMsg,
                                 MRASProtobufMsg_fields);
            break;
        }
        case BarometerDataMsg_t: {
            auto baro_msg = (BarometerDataMsg*) msg;
            // log("BarometerDataMsg: Pressure: %f Temperature: %f", baro_msg->pressure, baro_msg->temperature);

            MRASProtobufMsg protobufMsg = MRASProtobufMsg_init_default;
            protobufMsg.which_message = MRASProtobufMsg_barometer_data_tag;
            protobufMsg.message.barometer_data.pressure = baro_msg->pressure;
            protobufMsg.message.barometer_data.temperature = baro_msg->temperature;
            send_protobuf_serial(protobuf_outbuffer,
                                 sizeof(protobuf_outbuffer),
                                 &protobufMsg,
                                 MRASProtobufMsg_fields);
            break;
        }
        case GNSSDataMsg_t: {
            auto gnss_msg = (GNSSDataMsg*) msg;
//            log("GNSSDataMsg: Lat: %f  Lon: %f  Alt: %f  Fix: %d  SIV: %d",
//                gnss_msg->latitude,
//                gnss_msg->longitude,
//                gnss_msg->altitude,
//                gnss_msg->fixType,
//                gnss_msg->SIV);

            MRASProtobufMsg protobufMsg = MRASProtobufMsg_init_default;
            protobufMsg.which_message = MRASProtobufMsg_gnss_data_tag;
            protobufMsg.message.gnss_data = ProtobufGNSSDataMsg_init_default;
            protobufMsg.message.gnss_data.latitude = gnss_msg->latitude;
            protobufMsg.message.gnss_data.longitude = gnss_msg->longitude;
            protobufMsg.message.gnss_data.altitude = gnss_msg->altitude;
            protobufMsg.message.gnss_data.fixType = gnss_msg->fixType;
            protobufMsg.message.gnss_data.SIV = gnss_msg->SIV;
            send_protobuf_serial(protobuf_outbuffer,
                                 sizeof(protobuf_outbuffer),
                                 &protobufMsg,
                                 MRASProtobufMsg_fields);
            break;
        }
        default:
            break;
    }
}
