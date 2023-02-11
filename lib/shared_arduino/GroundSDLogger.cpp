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

    Serial.printf("Got message of type %d\n", msg->get_type());

    switch (msg->get_type()) {
        case ReceivedTelemetryMessageMsg_t: {
            Serial.println("Got new ReceivedTelemetryMessageMsg");
            auto system_message = (ReceivedTelemetryMessageMsg*) msg;
            TelemetryMessage *telemetry_message = system_message->telemetry_message;
            Serial.printf("New telemetry message type: %d\n", telemetry_message->get_type());
            switch (telemetry_message->get_type()) {
                case TelemetryDataMsg_t: {
                    Serial.println("Got new TelemetryDataMsg");
                    char buffer[255];
                    auto data_msg = (TelemetryDataMsg*) telemetry_message;
                    data_msg->to_csv(buffer, sizeof buffer);
                    Serial.printf("Logging telemetry: %s\n", buffer);
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
            Serial.print("Logging text: ");
            Serial.println(text_log_msg->text);
            log_file.print(text_log_msg->text);
            log_file.flush();
            break;
        }

        default:
            break;
    }
}
