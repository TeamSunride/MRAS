//
// Created by Tom Danvers on 01/06/2023.
//

#ifndef MRAS_BUZZERMESSAGE_H
#define MRAS_BUZZERMESSAGE_H

#include "SystemMessage.h"

struct BuzzerMsg : public SystemMessage {
    explicit BuzzerMsg(uint32_t _frequency, uint32_t _duration, bool _block) : SystemMessage(BuzzerMsg_t) {
        frequency = _frequency;
        duration = _duration;
        block = _block;
    }

    uint32_t frequency = 0;
    uint32_t duration = 0;
    bool block = false;
};

#endif //MRAS_BUZZERMESSAGE_H
