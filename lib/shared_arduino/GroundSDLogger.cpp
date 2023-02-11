//
// Created by Tom Danvers on 10/02/2023.
//

#include "GroundSDLogger.h"
#include "system_messages/ReceivedTelemetryMessageMsg.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "system_messages/TextLogMsg.h"

int8_t GroundSDLogger::loop() {
    if (!setup_complete) return -1;

    return 0;
}

void GroundSDLogger::on_message(SystemMessage *msg) {
    if (!setup_complete) return;

    switch (msg->get_type()) {
        case ReceivedTelemetryMessageMsg_t: {
            auto system_message = (ReceivedTelemetryMessageMsg*) msg;
            TelemetryMessage *telemetry_message = system_message->telemetry_message;
            switch (telemetry_message->get_type()) {
                case TelemetryDataMsg_t: {
                    char buffer[255];
                    auto data_msg = (TelemetryDataMsg*) telemetry_message;
                    data_msg->to_csv(buffer, sizeof buffer);
                    log_file.println(buffer);
                    log_file.flush();
                    break;
                }
                default:
                    break;
            }
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
