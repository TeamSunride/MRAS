//
// Created by Tom Danvers on 06/02/2023.
//

#include "RocketTelemetrySystem.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "system_messages/GNSSDataMsg.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/StateEstimatorMsg.h"

int8_t RocketTelemetrySystem::loop() {
    Module *mod = radio.getMod();
    if (telemetry_system_state != IDLE) {
        // check interrupt pin of radio and return if the radio is busy
        if (!mod->digitalRead(mod->getIrq())) {
            return 0;
        }
    }

    switch (telemetry_system_state) {
        case IDLE: {
            transmit_next_message();
            break;
        }
        case TX: {
            radio.finishTransmit();
            transmit_next_message();
            break;
        }
        case RX: {
            auto *msg = new TelemetryMessageReceivedMsg();
            if (read_new_message_from_buffer(msg)) {
                publish(msg);
            } else {
                log("CRC or radio error");
                delete msg;
            }
            break;
        }
    }

    return 0;
}

/**
 * On the rocket, we send a TelemetryDataMsg by default
 */
TelemetryMessageQueueMsg *RocketTelemetrySystem::get_default_message() {
    auto *message = new TelemetryDataMsg();

    memcpy(message, &telemetry_msg, sizeof(TelemetryDataMsg));

    auto *queue_message = new TelemetryMessageQueueMsg();
    queue_message->telemetry_message = message;
    queue_message->size = sizeof(TelemetryDataMsg);

    return queue_message;
}

void RocketTelemetrySystem::on_message(SystemMessage *msg) {
    switch (msg->get_type()) {
        case GNSSDataMsg_t:
            msg = (GNSSDataMsg *) msg;
            if (((GNSSDataMsg *) msg)->id == MAXM10s_ID) {
                telemetry_msg.altitude1 = (uint16_t) ((GNSSDataMsg *) msg)->altitude;
                telemetry_msg.latitude1 = ((GNSSDataMsg *) msg)->latitude;
                telemetry_msg.longitude1 = ((GNSSDataMsg *) msg)->longitude;
                telemetry_msg.fix_type1 = ((GNSSDataMsg *) msg)->fix_type;
                telemetry_msg.satellites1 = ((GNSSDataMsg *) msg)->SIV;
            }
            else if (((GNSSDataMsg *) msg)->id == SAMM10Q_ID) {
                telemetry_msg.altitude2 = (uint16_t) ((GNSSDataMsg *) msg)->altitude;
                telemetry_msg.latitude2 = ((GNSSDataMsg *) msg)->latitude;
                telemetry_msg.longitude2 = ((GNSSDataMsg *) msg)->longitude;
                telemetry_msg.fix_type2 = ((GNSSDataMsg *) msg)->fix_type;
                telemetry_msg.satellites2 = ((GNSSDataMsg *) msg)->SIV;
            }

            break;
        case AccelerometerDataMsg_t:
            telemetry_msg.x_acceleration = ((AccelerometerDataMsg *) msg)->acceleration[0];
            break;
        case BarometerDataMsg_t:
            telemetry_msg.pressure = ((BarometerDataMsg *) msg)->pressure;
            telemetry_msg.temperature = ((BarometerDataMsg *) msg)->temperature;
            break;
        case StateEstimatorMsg_t:
            telemetry_msg.altitude_estimate = ((StateEstimatorMsg *) msg)->estimatedAltitude;
            break;
    }
}
