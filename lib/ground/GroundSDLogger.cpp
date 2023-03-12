//
// Created by Tom Danvers on 10/02/2023.
//

#include "GroundSDLogger.h"
#include "system_messages/TelemetryMessageReceivedMsg.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "system_messages/TextLogMsg.h"
#include "system_messages/RadioStatusMsg.h"

int8_t GroundSDLogger::loop() {
    if (!setup_complete) return -1;

    return 0;
}

void GroundSDLogger::on_message(SystemMessage *msg) {
    if (!setup_complete) return;

    switch (msg->get_type()) {
        case ReceivedTelemetryMessageMsg_t: {
            auto system_message = (TelemetryMessageReceivedMsg *) msg;
            TelemetryMessage *telemetry_message = system_message->telemetry_message;
            switch (telemetry_message->get_type()) {
                case TelemetryDataMsg_t: {
                    char telemetry_string[255];
                    char log_string[255];
                    auto data_msg = (TelemetryDataMsg *) telemetry_message;
                    data_msg->to_csv(telemetry_string, sizeof telemetry_string);

                    // combine telemetry string with extra values on ground end
                    snprintf(log_string, 255, "%s,%f,%f,%d", telemetry_string, radio_status.RSSI, radio_status.SNR,
                             radio_status.PPS);
                    log_file.println(log_string);
                    Serial.println(log_string);
                    log_file.flush();
                    break;
                }
                default:
                    break;
            }
            break;
        }
        case RadioStatusMsg_t: {
            auto radio_status_msg = (RadioStatusMsg *) msg;
            memcpy(&radio_status, radio_status_msg, sizeof(RadioStatusMsg));
            break;
        }
        case TextLogMsg_t: {
            auto text_log_msg = (TextLogMsg *) msg;
            log_file.printf("#%s", text_log_msg->text);
            log_file.flush();
            break;
        }

        default:
            break;
    }
}
