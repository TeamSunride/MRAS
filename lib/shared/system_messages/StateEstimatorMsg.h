#ifndef MRAS_STATEESTIMATORMSG_H
#define MRAS_STATEESTIMATORMSG_H

#include "SystemMessage.h"

struct StateEstimatorMsg : public SystemMessage {
    explicit StateEstimatorMsg() : SystemMessage(StateEstimatorMsg_t) {}

    float estimatedAltitude = 0;
    float estimatedVelocity = 0;
};


#endif