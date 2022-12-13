//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_ACCELEROMETERDATAMSG_H
#define MRAS_ACCELEROMETERDATAMSG_H


#include "SystemMessage.h"
#include "Vector.h"


struct AccelerometerDataMsg : public SystemMessage {
    AccelerometerDataMsg() : SystemMessage(AccelerometerDataMsg_t) {}

    Vector<float, 3> acceleration = {0, 0, 0};

    uint64_t timestamp = 0;
};

#endif //MRAS_ACCELEROMETERDATAMSG_H
