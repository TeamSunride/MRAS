//
// Created by Tom Danvers on 04/02/2023.
//

#ifndef MRAS_TELEMETRYDATAMSG_H
#define MRAS_TELEMETRYDATAMSG_H

#include "TelemetryMessage.h"
#include <cstdint>

/**
 * @brief A message containing data from the rocket
 *
 * This message is used to send telemetry data from the rocket to the ground station.
 */
struct TelemetryDataMsg : public TelemetryMessage {
    TelemetryDataMsg() : TelemetryMessage(TelemetryDataMsg_t) {}

    int16_t x = 0;
    int16_t y = 0;
    int16_t z = 0;

    void to_csv(char *buffer, size_t buffer_size) const {
        snprintf(buffer, buffer_size, "%d,%d,%d", x, y, z);
    }
};

#endif //MRAS_TELEMETRYDATAMSG_H
