//
// Created by Tom Danvers on 06/02/2023.
//

#include "GroundTelemetrySystem.h"
#include "telemetry_messages/TransferWindowAckMsg.h"
#include "system_messages/RadioStatusMsg.h"

int8_t GroundTelemetrySystem::loop() {
    Module *mod = radio.getMod();
    if (telemetry_system_state != IDLE) {
        // check interrupt pin of radio and return if the radio is busy
        if (!mod->digitalRead(mod->getIrq())) {
            return 0;
        }
    }

    switch (telemetry_system_state) {
        case IDLE: {
            // ground station starts by receiving the next message
            start_receiving_next_message();
            break;
        }
        case TX: {
            radio.finishTransmit();
            transmit_next_message();
            break;
        }
        case RX: {
            auto* msg = new TelemetryMessageReceivedMsg();
            if (read_new_message_from_buffer(msg)) {
                publish(msg);
                packets_received++;
            } else {
                delete msg;
            }
        }
    }

    if (millis() - last_PPS_count > 1000) {
        last_PPS_count = millis();
        PPS = packets_received;
        packets_received = 0;

        auto* msg = new RadioStatusMsg();
        msg->PPS = PPS;
        msg->RSSI = radio.getRSSI();
        msg->SNR = radio.getSNR();
        publish(msg);
    }

    return 0;
}

TelemetryMessageQueueMsg *GroundTelemetrySystem::get_default_message() {
    auto *message = new TransferWindowAckMsg();
    auto *queue_message = new TelemetryMessageQueueMsg();
    queue_message->telemetry_message = message;
    queue_message->size = sizeof(TransferWindowAckMsg);
    return queue_message;
}
