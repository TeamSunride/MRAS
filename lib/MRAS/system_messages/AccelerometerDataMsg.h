//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_ACCELEROMETERDATAMSG_H
#define MRAS_ACCELEROMETERDATAMSG_H


#include "SystemMessage.h"
#include "Vector.h"

struct AccelerometerDataMsg : public SystemMessage {
    explicit AccelerometerDataMsg(SystemMessageType accel_msg_type) : SystemMessage(accel_msg_type) {}

    Vector<float, 3> acceleration = {0, 0, 0};
};

#endif //MRAS_ACCELEROMETERDATAMSG_H
