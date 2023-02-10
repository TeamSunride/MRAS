//
// Created by Tom Danvers on 10/02/2023.
//

#ifndef MRAS_TEXTLOGMSG_H
#define MRAS_TEXTLOGMSG_H

#include "SystemMessage.h"

struct TextLogMsg : public SystemMessage {
    TextLogMsg() : SystemMessage(TextLogMsg_t) {}

    char text[255] = {};
};

#endif //MRAS_TEXTLOGMSG_H
