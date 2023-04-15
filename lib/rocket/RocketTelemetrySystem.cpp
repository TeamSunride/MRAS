//
// Created by Tom Danvers on 06/02/2023.
//

#include "RocketTelemetrySystem.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "system_messages/GNSSDataMsg.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/StateEstimatorMsg.h"
#include "system_messages/EventDetectorMsg.h"

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
    message->altitude = altitude;
    message->latitude = latitude;
    message->longitude = longitude;
    message->fix_type = fix_type;
    message->satellites = satellites;
    message->y_acceleration = y_acceleration;
    message->pressure = pressure;
    message->temperature = temperature;
    message->altitude_estimate = altitude_estimate;
    message->event = event;
    message->phase = phase;

    auto *queue_message = new TelemetryMessageQueueMsg();
    queue_message->telemetry_message = message;
    queue_message->size = sizeof(TelemetryDataMsg);

    return queue_message;
}

void RocketTelemetrySystem::on_message(SystemMessage *msg) {
    switch (msg->get_type()) {
        case GNSSDataMsg_t:
            altitude = (uint16_t) ((GNSSDataMsg *) msg)->altitude;
            latitude = ((GNSSDataMsg *) msg)->latitude;
            longitude = ((GNSSDataMsg *) msg)->longitude;
            fix_type = ((GNSSDataMsg *) msg)->fix_type;
            satellites = ((GNSSDataMsg *) msg)->SIV;
            break;
        case AccelerometerDataMsg_t:
            y_acceleration = ((AccelerometerDataMsg *) msg)->acceleration[1];
            break;
        case BarometerDataMsg_t:
            pressure = ((BarometerDataMsg *) msg)->pressure;
            temperature = ((BarometerDataMsg *) msg)->temperature;
            break;
        case StateEstimatorMsg_t:
            altitude_estimate = ((StateEstimatorMsg *) msg)->estimatedAltitude;
            break;
        case EventDetectorMsg_t:
            event = ((EventDetectorMsg *) msg)->event;
            phase = ((EventDetectorMsg *) msg)->phase;
            break;
    }
}
