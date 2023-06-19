//
// Created by Tom Danvers on 11/03/2023.
//

#ifndef MRAS_RADIOSTATUSMSG_H
#define MRAS_RADIOSTATUSMSG_H

#include "SystemMessage.h"
#include "MRAS_Config.h"

// create RadioStatusMessage SystemMessage
struct RadioStatusMsg : SystemMessage {
    RadioStatusMsg() : SystemMessage(RadioStatusMsg_t) {}

    float RSSI = 0;
    float SNR = 0;
    uint16_t PPS = 0;

    void to_line_protocol(char *buffer, size_t size) {
        snprintf(buffer, size, "radio_status,stage=%s RSSI=%f,SNR=%f,PPS=%d", STAGE_NAME, RSSI, SNR,
                 PPS);
    }
};

#endif //MRAS_RADIOSTATUSMSG_H
