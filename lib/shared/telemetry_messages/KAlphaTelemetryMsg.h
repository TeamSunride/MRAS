//
// Created by Tom Danvers on 17/06/2023.
//

#ifndef MRAS_KALPHATELEMETRYMSG_H
#define MRAS_KALPHATELEMETRYMSG_H

#include <cstdint>

struct KAlphaTelemetryMsg {
    float latitude = 0;
    float longitude = 0;
    uint8_t gps_state = 0b00000000;
    uint16_t gps_altitude = 0;

    int16_t x_acceleration = 0;
    float pressure = 0;
    uint8_t temperature = 0;
    uint16_t pressure_altitude = 0;

    uint8_t battery_voltage = 0;
};

#endif //MRAS_KALPHATELEMETRYMSG_H
