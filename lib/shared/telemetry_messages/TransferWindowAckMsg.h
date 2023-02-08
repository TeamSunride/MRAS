//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_TRANSFERWINDOWACKMSG_H
#define MRAS_TRANSFERWINDOWACKMSG_H

#include "TelemetryMessage.h"

struct TransferWindowAckMsg : public TelemetryMessage {
    TransferWindowAckMsg() : TelemetryMessage(TransferWindowAckMsg_t) {}
};

#endif //MRAS_TRANSFERWINDOWACKMSG_H
