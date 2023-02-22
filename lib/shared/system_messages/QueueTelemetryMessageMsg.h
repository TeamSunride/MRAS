//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_QUEUETELEMETRYMESSAGEMSG_H
#define MRAS_QUEUETELEMETRYMESSAGEMSG_H

#include <cstdio>
#include "SystemMessage.h"
#include "TelemetryMessage.h"

/**
 * @brief A SystemMessage that is used to queue a TelemetryMessage for sending to the ground or the rocket
 *
 * This message is used by the TelemetrySystem to queue TelemetryMessages for sending to the ground or the rocket
 */
struct QueueTelemetryMessageMsg : public SystemMessage {
    QueueTelemetryMessageMsg() : SystemMessage(QueueTelemetryMessageMsg_t) {}

    ~QueueTelemetryMessageMsg() {
        delete telemetry_message;
    }

    // TODO: change how the memory is allocated here so it acts like the ReceiveTelemetryMessageMsg

    /*
     * A pointer to the TelemetryMessage that we want to send to the ground.
     *
     * This TelemetryMessage must be allocated on the heap.
    */
    TelemetryMessage *telemetry_message = nullptr;
    size_t size = 0;
};

#endif //MRAS_QUEUETELEMETRYMESSAGEMSG_H
