//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_GYRODATAMSG_H
#define MRAS_GYRODATAMSG_H

#include "SystemMessage.h"
#include "Vector.h"

struct GyroDataMsg : public SystemMessage {
    GyroDataMsg() : SystemMessage(GyroDataMsg_t) {}

    Vector<float, 3> gyro = {0, 0, 0};
};

#endif //MRAS_GYRODATAMSG_H
