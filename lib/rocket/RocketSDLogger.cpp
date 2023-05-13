//
// Created by Tom Danvers on 10/02/2023.
//

#include "RocketSDLogger.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/GyroDataMsg.h"
#include "system_messages/MagnetometerDataMsg.h"
#include "system_messages/GNSSDataMsg.h"
#include "system_messages/StateEstimatorMsg.h"
#include "timestamp.h"
#include "MRAS_Config.h"

int8_t RocketSDLogger::loop() {
    if (!setup_complete) return -1;

    if (millis() - last_log_entry >= 1) {
        // I ADORE you GitHub Copilot
        log_file.printf(
                "%f,%f,%f"
                ",%f,%f,%f"
                ",%f,%f,%f"
                ",%f,%f,%f"
                ",%f,%f"
                ",%f,%f,%f,%d,%d"
                ",%f,%f,%f,%d,%d"
                ",%f,%f,%llu\n",
                data.accel[0], data.accel[1], data.accel[2],
                data.accel_high_G[0], data.accel_high_G[1], data.accel_high_G[2],
                data.gyro[0], data.gyro[1], data.gyro[2],
                data.mag[0], data.mag[1], data.mag[2],
                data.pressure, data.temperature,
                data.latitude1, data.longitude1, data.altitude1, data.fix_type1, data.SIV1,
                data.latitude2, data.longitude2, data.altitude2, data.fix_type2, data.SIV2,
                data.altitude_estimate, data.velocity_estimate, getTimestampMillis());
        last_log_entry = millis();
    }

    if (millis() - last_flush > 1000) {
        log_file.flush();
        last_flush = millis();
    }

    return 0;
}

void RocketSDLogger::on_message(SystemMessage *msg) {
    if (!setup_complete) return;

    switch (msg->get_type()) {
        case AccelerometerDataMsg_t: {
            auto new_msg = (AccelerometerDataMsg *) msg;
            data.accel = new_msg->acceleration;
            break;
        }
        case HighGAccelerometerDataMsg_t: {
            auto new_msg = (AccelerometerDataMsg *) msg;
            data.accel_high_G = new_msg->acceleration;
            break;
        }
        case BarometerDataMsg_t: {
            auto new_msg = (BarometerDataMsg *) msg;
            data.pressure = new_msg->pressure;
            data.temperature = new_msg->temperature;
            break;
        }
        case GyroDataMsg_t: {
            auto new_msg = (GyroDataMsg *) msg;
            data.gyro = new_msg->gyro;
            break;
        }
        case MagnetometerDataMsg_t: {
            auto new_msg = (MagnetometerDataMsg*) msg;
            data.mag = new_msg->mag;
            break;
        }

        case GNSSDataMsg_t: {
            auto new_msg = (GNSSDataMsg*) msg;

            if (new_msg->id == MAXM10s_ID) {
                data.latitude1 = new_msg->latitude;
                data.longitude1 = new_msg->longitude;
                data.altitude1 = new_msg->altitude;
                data.fix_type1 = new_msg->fix_type;
                data.SIV1 = new_msg->SIV;
            }
            else if (new_msg->id == SAMM10Q_ID) {
                data.latitude2 = new_msg->latitude;
                data.longitude2 = new_msg->longitude;
                data.altitude2 = new_msg->altitude;
                data.fix_type2 = new_msg->fix_type;
                data.SIV2 = new_msg->SIV;
            }
            break;
        }
        case StateEstimatorMsg_t: {
            auto new_msg = (StateEstimatorMsg*) msg;
            data.altitude_estimate = new_msg->estimatedAltitude;
            data.velocity_estimate = new_msg->estimatedVelocity;
            break;
        }
//        case TextLogMsg_t: {
//            // make sure the data file is flushed before we log any text
//            auto text_log_msg = (TextLogMsg *) msg;
//            log_file.printf("#%s", text_log_msg->text);
//            log_file.flush();
//            break;
//        }
        default:
            break;
    }
}
