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

    float latitude = 0;
    float longitude = 0;
    uint16_t altitude = 0;
    uint8_t fix_type = 0;
    uint8_t satellites = 0;

    void to_csv(char *buffer, size_t buffer_size) const {
        //snprintf(buffer, buffer_size, "%d,%d,%d", x, y, z);
        //snprintf(buffer, buffer_size, "%f,%f,%d", latitude, longitude, altitude);
        snprintf(buffer, buffer_size, "%f,%f,%d,%d,%d", latitude, longitude, altitude, fix_type, satellites);
    }
};

#endif //MRAS_TELEMETRYDATAMSG_H
