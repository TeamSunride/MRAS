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

    float latitude1 = 0;
    float longitude1 = 0;
    uint16_t altitude1 = 0;
    uint8_t fix_type1 = 0;
    uint8_t satellites1 = 0;
    float latitude2 = 0;
    float longitude2 = 0;
    uint16_t altitude2 = 0;
    uint8_t fix_type2 = 0;
    uint8_t satellites2 = 0;
    float x_acceleration = 0;
    float pressure = 0;
    float temperature = 0;
    float altitude_estimate = 0;

    void to_csv(char *buffer, size_t buffer_size) const {
        snprintf(buffer, buffer_size, "%f,%f,%d,%d,%d,%f,%f,%d,%d,%d,%f,%f,%f,%f", latitude1, longitude1, altitude1, fix_type1, satellites1,
                 latitude2, longitude2, altitude2, fix_type2, satellites2,
                 x_acceleration, pressure, temperature, altitude_estimate);
    }

    void to_line_protocol(char *buffer, size_t buffer_size) const {
        snprintf(buffer, buffer_size, "TelemetryDataMsg latitude1=%f,longitude1=%f,altitude1=%d,fix_type1=%d,satellites1=%d,latitude2=%f,longitude2=%f,altitude2=%d,fix_type2=%d,satellites2=%d,x_acceleration=%f,pressure=%f,temperature=%f,altitude_estimate=%f",
                 latitude1, longitude1, altitude1, fix_type1, satellites1,
                 latitude2, longitude2, altitude2, fix_type2, satellites2,
                 x_acceleration, pressure, temperature, altitude_estimate);
    }
};

#endif //MRAS_TELEMETRYDATAMSG_H
