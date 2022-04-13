//
// Created by Tom Danvers on 05/04/2022.
// 2022 TeamSunride.
//

#include "Barometer_MS5607.h"

int8_t Barometer_MS5607::begin() {
    if (_sensor.begin()) {
        // lowest oversample rate to reduce data acquisition time
        // this should be replaced with a different approach in future
        _sensor.setOSR(256);
        return 0;
    } else {
        return 1;
    }
}

int8_t Barometer_MS5607::readData() {
    if (_sensor.readDigitalValue()) {
        _temperature = _sensor.getTemperature();
        _pressure = _sensor.getPressure();
        return 0;
    } else {
        return 1;
    }
}
