//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_MAGNETOMETERDATAMSG_H
#define MRAS_MAGNETOMETERDATAMSG_H


#include "SystemMessage.h"
#include "Vector.h"


struct MagnetometerDataMsg : public SystemMessage {
    MagnetometerDataMsg() : SystemMessage(MagnetometerDataMsg_t) {}

    Vector<float, 3> mag = {0, 0, 0};
};

#endif //MRAS_MAGNETOMETERDATAMSG_H
