//
// Created by Tom Danvers on 10/02/2023.
//

#include "RocketSDLogger.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/GyroDataMsg.h"
#include "system_messages/MagnetometerDataMsg.h"
#include "system_messages/GNSSDataMsg.h"

int8_t RocketSDLogger::loop() {
    if (!setup_complete) return -1;

    if (millis() - last_log_entry > 1) {
        // I ADORE you GitHub Copilot
        data_file.printf(
                "%f,%f,%f"
                ",%f,%f,%f"
                ",%f,%f,%f"
                ",%f,%f,%f"
                ",%f,%f"
                ",%f,%f,%f,%d,%d\n",
                data.accel[0], data.accel[1], data.accel[2],
                data.accel_high_G[0], data.accel_high_G[1], data.accel_high_G[2],
                data.gyro[0], data.gyro[1], data.gyro[2],
                data.mag[0], data.mag[1], data.mag[2],
                data.pressure, data.temperature,
                data.latitude, data.longitude, data.altitude, data.fix_type, data.SIV);
        data_file.flush();
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
            data.latitude = new_msg->latitude;
            data.longitude = new_msg->longitude;
            
            break;
        }
        case TextLogMsg_t: {
            auto text_log_msg = (TextLogMsg *) msg;
            log_file.print(text_log_msg->text);
            log_file.flush();
            break;
        }
        default:
            break;
    }
}
