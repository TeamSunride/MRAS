//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_BAROMETERDATAMSG_H
#define MRAS_BAROMETERDATAMSG_H

#include "SystemMessage.h"

struct BarometerDataMsg : public SystemMessage {
    BarometerDataMsg() : SystemMessage(BarometerDataMsg_t) {}

    float pressure = 0;
    float temperature = 0;
};

#endif //MRAS_BAROMETERDATAMSG_H
