//
// Created by Tom Danvers on 10/02/2023.
//

#include "GroundSDLogger.h"
#include "system_messages/TelemetryMessageReceivedMsg.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "system_messages/TextLogMsg.h"
#include "system_messages/RadioStatusMsg.h"
#include "telemetry_messages/KAlphaTelemetryMsg.h"

int8_t GroundSDLogger::loop() {
    if (!setup_complete) return -1;

    return 0;
}

void GroundSDLogger::on_message(SystemMessage *msg) {

    switch (msg->get_type()) {
        case ReceivedTelemetryMessageMsg_t: {
            auto system_message = (TelemetryMessageReceivedMsg *) msg;
            TelemetryMessage *telemetry_message = system_message->telemetry_message;
            switch (telemetry_message->get_type()) {
                case TelemetryDataMsg_t: {
                    char telemetry_string[255];
                    char log_string[255];
                    char line_protocol_string[500];
                    auto data_msg = (TelemetryDataMsg *) telemetry_message;
                    data_msg->to_csv(telemetry_string, sizeof telemetry_string);
                    data_msg->to_line_protocol(line_protocol_string, sizeof line_protocol_string);

                    // combine telemetry string with extra values on ground end
                    snprintf(log_string, 255, "%s,%f,%f,%d", telemetry_string, radio_status.RSSI, radio_status.SNR,
                             radio_status.PPS);
                    Serial.println(line_protocol_string);

                    if (setup_complete) {
                        log_file.println(log_string);
                    }
                    break;
                }
                case KAlphaTelemetryMsg_Packed_t : {
                    char telemetry_string[255];
                    char log_string[255];
                    char line_protocol_string[500];
                    KAlphaTelemetryMsg data_msg;
                    unpack_kalpha_telemetry_msg((KAlphaTelemetryMsg_Packed *) telemetry_message, &data_msg);
                    data_msg.to_csv(telemetry_string, sizeof telemetry_string);
                    data_msg.to_line_protocol(line_protocol_string, sizeof line_protocol_string);

                    // combine telemetry string with extra values on ground end
                    snprintf(log_string, 255, "%s,%f,%f,%d", telemetry_string, radio_status.RSSI, radio_status.SNR,
                             radio_status.PPS);
                    Serial.println(line_protocol_string);

                    if (setup_complete) {
                        log_file.println(log_string);
                    }
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
            char line_protocol_string[500];
            radio_status_msg->to_line_protocol(line_protocol_string, sizeof line_protocol_string);
            Serial.println(line_protocol_string);
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
