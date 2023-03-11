//
// Created by Tom Danvers on 11/03/2023.
//

#ifndef MRAS_BUZZERINTERFACE_H
#define MRAS_BUZZERINTERFACE_H

#include "Subsystem.h"

class BuzzerInterface : public Subsystem {
public:
    using Subsystem::Subsystem;

    SUBSYSTEM_NAME("BuzzerInterface")

    SUBSYSTEM_NO_MESSAGE_HANDLER

    virtual void _buzzer(uint16_t frequency, uint32_t duration) = 0;
};

#endif //MRAS_BUZZERINTERFACE_H
