//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_TELEMETRYDATAMSG_H
#define MRAS_TELEMETRYDATAMSG_H

#include "TelemetryMessage.h"
#include <cstdint>

struct TelemetryDataMsg : public TelemetryMessage {
    TelemetryDataMsg() : TelemetryMessage(TelemetryDataMsg_t) {}

    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;
};

#endif //MRAS_TELEMETRYDATAMSG_H
