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
    float y_acceleration = 0;
    float pressure = 0;
    float temperature = 0;
    float altitude_estimate = 0;

    void to_csv(char *buffer, size_t buffer_size) const {
        snprintf(buffer, buffer_size, "%f,%f,%d,%d,%d,%f,%f,%f,%f", latitude, longitude, altitude, fix_type, satellites,
                 y_acceleration, pressure, temperature, altitude_estimate);
    }
};

#endif //MRAS_TELEMETRYDATAMSG_H
