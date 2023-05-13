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

        radio.finishTransmit();
    }

    switch (telemetry_system_state) {
        case IDLE: {
            transmit_next_message();
            break;
        }
        case TX: {
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

    message->altitude1 = altitude1;
    message->latitude1 = latitude1;
    message->longitude1 = longitude1;
    message->fix_type1 = fix_type1;
    message->satellites1 = satellites1;

    message->altitude2 = altitude2;
    message->latitude2 = latitude2;
    message->longitude2 = longitude2;
    message->fix_type2 = fix_type2;
    message->satellites2 = satellites2;

    message->y_acceleration = y_acceleration;
    message->pressure = pressure;
    message->temperature = temperature;
    message->altitude_estimate = altitude_estimate;

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
                altitude1 = (uint16_t) ((GNSSDataMsg *) msg)->altitude;
                latitude1 = ((GNSSDataMsg *) msg)->latitude;
                longitude1 = ((GNSSDataMsg *) msg)->longitude;
                fix_type1 = ((GNSSDataMsg *) msg)->fix_type;
                satellites1 = ((GNSSDataMsg *) msg)->SIV;
            }
            else if (((GNSSDataMsg *) msg)->id == SAMM10Q_ID) {
                altitude2 = (uint16_t) ((GNSSDataMsg *) msg)->altitude;
                latitude2 = ((GNSSDataMsg *) msg)->latitude;
                longitude2 = ((GNSSDataMsg *) msg)->longitude;
                fix_type2 = ((GNSSDataMsg *) msg)->fix_type;
                satellites2 = ((GNSSDataMsg *) msg)->SIV;
            }

            break;
        case AccelerometerDataMsg_t:
            x_acceleration = ((AccelerometerDataMsg *) msg)->acceleration[0];
            break;
        case BarometerDataMsg_t:
            pressure = ((BarometerDataMsg *) msg)->pressure;
            temperature = ((BarometerDataMsg *) msg)->temperature;
            break;
        case StateEstimatorMsg_t:
            altitude_estimate = ((StateEstimatorMsg *) msg)->estimatedAltitude;
            break;
    }
}
