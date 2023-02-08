//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_RECEIVEDTELEMETRYMESSAGEMSG_H
#define MRAS_RECEIVEDTELEMETRYMESSAGEMSG_H

#include <cstdio>
#include "SystemMessage.h"
#include "TelemetryMessage.h"

struct ReceivedTelemetryMessageMsg : public SystemMessage {
    ReceivedTelemetryMessageMsg() : SystemMessage(ReceivedTelemetryMessageMsg_t) {}

    TelemetryMessage* telemetry_message = nullptr;
};

#endif //MRAS_RECEIVEDTELEMETRYMESSAGEMSG_H
