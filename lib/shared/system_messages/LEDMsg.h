//
// Created by Tom Danvers on 01/06/2023.
//

#ifndef MRAS_LEDMSG_H
#define MRAS_LEDMSG_H

#include "SystemMessage.h"

struct LEDMsg : public SystemMessage {
    explicit LEDMsg(uint8_t _r, uint8_t _g, uint8_t _b, uint8_t _pixel) : SystemMessage(LEDMsg_t) {
        r = _r;
        g = _g;
        b = _b;
        pixel = _pixel;
    }

    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t pixel = 0;
};

#endif //MRAS_LEDMSG_H
