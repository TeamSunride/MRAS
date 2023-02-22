//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_TRANSFERWINDOWINITMSG_H
#define MRAS_TRANSFERWINDOWINITMSG_H

#include "TelemetryMessage.h"

/**
 * @brief A message sent by the rocket to initiate a transfer window
 *
 * This message is sent by the rocket in order to initiate a new transfer opportunity.
 * The ground station will respond with a TransferWindowAckMsg if it has no data to send
 * or a TelemetryMessage if it does.
 */
struct TransferWindowInitMsg : public TelemetryMessage {
    TransferWindowInitMsg() : TelemetryMessage(TransferWindowInitMsg_t) {}
};

#endif //MRAS_TRANSFERWINDOWINITMSG_H
