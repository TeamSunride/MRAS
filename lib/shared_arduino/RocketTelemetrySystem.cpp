//
// Created by Tom Danvers on 06/02/2023.
//

#include "RocketTelemetrySystem.h"

int8_t RocketTelemetrySystem::loop() {
    Module *mod = radio.getMod();
    if (telemetry_system_state != IDLE) {
        // check interrupt pin of radio and return if the radio is busy
        if (!mod->digitalRead(mod->getIrq())) {
            return 0;
        }

        radio.finishTransmit();
    }

    switch (telemetry_system_state) { return 0;
        case IDLE: {
            transmit_next_message();
            break;
        }
        case TX: {
            transmit_next_message();
            break;
        }
        case RX: {
            ReceivedTelemetryMessageMsg* msg = nullptr;
            if (read_new_message_from_buffer(msg)) {
                publish(msg);
            } else {
                log("CRC or radio error");
            }
        }
    }
}
