//
// Created by Tom Danvers on 19/06/2022.
// 2022 TeamSunride.
//

#include "GPS_ZOE_M8Q.h"

int8_t GPS_ZOE_M8Q::begin() {
    int8_t returnStatusCode = 0;

    Serial.println("Setting up ZOE-M8Q");

    if (GNSS.begin()) {
        Serial.println("GPS startup success");
    }else {
        Serial.println("GPS startup failure");
        return -1;
    }

    // Set the I2C port to output UBX only (turn off NMEA noise)
    if (!GNSS.setI2COutput(COM_TYPE_UBX)) returnStatusCode = -2;

    if (!GNSS.setNavigationFrequency(NAVIGATION_FREQUENCY)) returnStatusCode = -3;

    // Tell the GNSS to "send" each solution
    if (!GNSS.setAutoPVT(true)) returnStatusCode = -4;

    // Save the current settings to flash and BBR
    if (!GNSS.saveConfiguration()) returnStatusCode = -5;

    if (returnStatusCode != 0) {
        Serial.println("GPS setup failed. Status code: " + String(returnStatusCode));
    }

    return returnStatusCode;
}

int8_t GPS_ZOE_M8Q::readData() {
    // Calling getPVT returns true if there actually is a fresh navigation solution available.
    // Start the reading only when valid LLH is available
    if (GNSS.getPVT() && !GNSS.getInvalidLlh()) {
        // convert lat and long to degrees
        _latitude = (float) (GNSS.getLatitude() / 1e7);
        _longitude = (float) (GNSS.getLongitude() / 1e7);
        _altitude = (float) (GNSS.getAltitudeMSL() / 1e3);
        _satellites_in_view = GNSS.getSIV();
        _fix_type = GNSS.getFixType();
    }

    return 0;
}
