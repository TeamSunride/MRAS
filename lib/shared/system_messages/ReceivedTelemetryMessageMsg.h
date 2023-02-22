//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_RECEIVEDTELEMETRYMESSAGEMSG_H
#define MRAS_RECEIVEDTELEMETRYMESSAGEMSG_H

#include <cstdio>
#include "SystemMessage.h"
#include "TelemetryMessage.h"

/**
 * @brief A SystemMessage that is output by the TelemetrySystem when a TelemetryMessage is received from the ground or the rocket
 */
struct ReceivedTelemetryMessageMsg : public SystemMessage {
    ReceivedTelemetryMessageMsg() : SystemMessage(ReceivedTelemetryMessageMsg_t) {
        telemetry_message = (TelemetryMessage*) radio_buffer;
    }

    /**
     * A pointer to the TelemetryMessage that was received from the ground or the rocket
     */
    TelemetryMessage* telemetry_message;
private:
    int8_t radio_buffer[255] = {};
};

#endif //MRAS_RECEIVEDTELEMETRYMESSAGEMSG_H
