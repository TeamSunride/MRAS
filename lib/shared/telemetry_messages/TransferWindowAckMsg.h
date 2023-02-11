//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_TRANSFERWINDOWACKMSG_H
#define MRAS_TRANSFERWINDOWACKMSG_H

#include "TelemetryMessage.h"

/**
 * @brief A message sent by the ground station to acknowledge a transfer window
 *
 * This message is sent by the ground station in response to a TransferWindowInitMsg
 * in the case where it does not have any data to send to the rocket.
 */
struct TransferWindowAckMsg : public TelemetryMessage {
    TransferWindowAckMsg() : TelemetryMessage(TransferWindowAckMsg_t) {}
};

#endif //MRAS_TRANSFERWINDOWACKMSG_H
