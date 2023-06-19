//
// Created by Tom Danvers on 18/06/2023.
//
#include "KAlphaTelemetryMsg.h"
int max(int a, int b) {
    return a > b ? a : b;
}

int min(int a, int b) {
    return a < b ? a : b;
}

void unpack_kalpha_telemetry_msg(KAlphaTelemetryMsg_Packed *packed_msg, KAlphaTelemetryMsg *msg) {
    msg->latitude = packed_msg->latitude;
    msg->longitude = packed_msg->longitude;

    // fix type: 2 bits, SIV: 6 bits
    msg->fix_type = (packed_msg->gps_state & 0b11000000) >> 6;
    msg->satellites = packed_msg->gps_state & 0b00111111;

    // altitude in meters, with an offset of -10000m applied to account for negative altitudes
    msg->gnss_altitude = (float) packed_msg->gnss_altitude - 10000;
    msg->pressure_altitude = (float) packed_msg->pressure_altitude - 10000;
    msg->max_pressure_altitude = (float) packed_msg->max_pressure_altitude - 10000;

    msg->x_acceleration = packed_msg->x_acceleration;
    msg->temperature = packed_msg->temperature;
    msg->batt_voltage = packed_msg->batt_voltage;
}

void pack_kalpha_telemetry_msg(KAlphaTelemetryMsg *msg, KAlphaTelemetryMsg_Packed *packed_msg) {
    packed_msg->latitude = msg->latitude;
    packed_msg->longitude = msg->longitude;

    // fix type: 2 bits, SIV: 6 bits
    packed_msg->gps_state = ((msg->fix_type & 0b00000011) << 6) | (msg->satellites & 0b00111111);

    // altitude in meters, with an offset of -10000m applied to account for negative altitudes
    packed_msg->gnss_altitude = (uint16_t) (msg->gnss_altitude + 10000);
    packed_msg->pressure_altitude = (uint16_t) (msg->pressure_altitude + 10000);
    packed_msg->max_pressure_altitude = (uint16_t) (msg->max_pressure_altitude + 10000);

    packed_msg->x_acceleration = msg->x_acceleration;
    packed_msg->temperature = (uint8_t) max(0, min(255, msg->temperature));

    // change this to something more serious soon
    packed_msg->batt_voltage = 10;
}
