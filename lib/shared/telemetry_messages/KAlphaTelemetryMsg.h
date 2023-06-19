//
// Created by Tom Danvers on 17/06/2023.
//

#ifndef MRAS_KALPHATELEMETRYMSG_H
#define MRAS_KALPHATELEMETRYMSG_H

#include <cstdint>
#include <cstdio>
#include "TelemetryMessage.h"
#include "MRAS_Config.h"

struct KAlphaTelemetryMsg_Packed : TelemetryMessage {
    KAlphaTelemetryMsg_Packed() : TelemetryMessage(KAlphaTelemetryMsg_Packed_t) {}

    float latitude = 0;
    float longitude = 0;
    // fix type: 2 bits, SIV: 6 bits
    uint8_t gps_state = 0b00000000;

    // altitude in meters, with an offset of -10000m applied to account for negative altitudes
    uint16_t gnss_altitude = 0;
    uint16_t pressure_altitude = 0;
    uint16_t max_pressure_altitude = 0;

    // this could be an int but lots of effort to change LSM6DSO32 lib.....
    // I feel like I would get shot if I cast from float to int here
    // .... but it's tempting
    float x_acceleration = 0;

    uint8_t temperature = 0;
    uint8_t batt_voltage = 0;
};

struct KAlphaTelemetryMsg {
    float latitude = 0;
    float longitude = 0;
    uint8_t fix_type = 0;
    uint8_t satellites = 0;

    // altitude in meters, with an offset of -10000m applied to account for negative altitudes
    float gnss_altitude = 0;
    float pressure_altitude = 0;
    float max_pressure_altitude = 0;

    float x_acceleration = 0;
    float temperature = 0;
    uint8_t batt_voltage = 0;

    void to_csv(char *buffer, size_t buffer_size) const {
        snprintf(buffer, buffer_size, "%f,%f,%d,%d,%f,%f,%f,%f,%f,%d",
                 latitude, longitude, fix_type, satellites,
                 gnss_altitude, pressure_altitude, max_pressure_altitude,
                 x_acceleration, temperature, batt_voltage);
    }

    void to_line_protocol(char *buffer, size_t buffer_size) const {
        snprintf(buffer, buffer_size,
                 "ka_sensors,stage=%s x_acceleration=%f,temperature=%f,batt_voltage=%d,"
                 "pressure_altitude=%f,max_pressure_altitude=%f\n"
                 "ka_position,stage=%s,fix=%d lat=%f,lon=%f,alt=%f,fix=%d,SIV=%d\n",
                 STAGE_NAME,
                 x_acceleration, temperature, batt_voltage, pressure_altitude, max_pressure_altitude,
                 STAGE_NAME,
                 fix_type, latitude, longitude, gnss_altitude, fix_type, satellites
                 );
    }
};

void pack_kalpha_telemetry_msg(KAlphaTelemetryMsg *msg, KAlphaTelemetryMsg_Packed *packed_msg);

void unpack_kalpha_telemetry_msg(KAlphaTelemetryMsg_Packed *packed_msg, KAlphaTelemetryMsg *msg);

#endif //MRAS_KALPHATELEMETRYMSG_H
