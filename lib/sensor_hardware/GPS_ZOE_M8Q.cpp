//
// Created by Tom Danvers on 19/06/2022.
// 2022 TeamSunride.
//

#include "GPS_ZOE_M8Q.h"

int8_t GPS_ZOE_M8Q::begin() {
    int8_t returnStatusCode = 0;

    // Set the I2C port to output UBX only (turn off NMEA noise)
    if (!GNSS.begin()) returnStatusCode = -1;

    // Produce two solutions per second
    if (!GNSS.setI2COutput(COM_TYPE_UBX)) -2;

    if (!GNSS.setNavigationFrequency(5)) -3;

    // Tell the GNSS to "send" each solution
    if (!GNSS.setAutoPVT(true)) -4;

    // Save the current settings to flash and BBR
    if (!GNSS.saveConfiguration()) -5;

    return returnStatusCode;
}

int8_t GPS_ZOE_M8Q::readData() {
    // Calling getPVT returns true if there actually is a fresh navigation solution available.
    // Start the reading only when valid LLH is available
    if (GNSS.getPVT() && !GNSS.getInvalidLlh()) {
        // convert lat and long to degrees
        _latitude = (float) (GNSS.getLatitude() / 1e7);
        _longitude = (float) (GNSS.getLongitude() / 1e7);
        _altitude = (float) (GNSS.getAltitude() / 1e3);
        _satellites_in_view = GNSS.getSIV();
        _fix_type = GNSS.getFixType();
    }

    return 0;
}
