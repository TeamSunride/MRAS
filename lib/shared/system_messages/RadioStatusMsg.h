//
// Created by Tom Danvers on 11/03/2023.
//

#ifndef MRAS_RADIOSTATUSMSG_H
#define MRAS_RADIOSTATUSMSG_H

#include "SystemMessage.h"

// create RadioStatusMessage SystemMessage
struct RadioStatusMsg : SystemMessage {
    RadioStatusMsg() : SystemMessage(RadioStatusMsg_t) {}

    float RSSI = 0;
    float SNR = 0;
    uint16_t PPS = 0;
};

#endif //MRAS_RADIOSTATUSMSG_H
