//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_TRANSFERWINDOWINITMSG_H
#define MRAS_TRANSFERWINDOWINITMSG_H

#include "TelemetryMessage.h"

struct TransferWindowInitMsg : public TelemetryMessage {
    TransferWindowInitMsg() : TelemetryMessage(TransferWindowInitMsg_t) {}
};

#endif //MRAS_TRANSFERWINDOWINITMSG_H
