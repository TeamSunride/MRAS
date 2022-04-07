//
// Created by Tom Danvers on 05/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_BAROMETER_H
#define MRASV2_BAROMETER_H

#include "Sensor.h"

/*
 * Barometer interface. To be implemented by an actual sensor class.
 */
class Barometer : public Sensor {
public:
    /*
     * Get pressure from the Barometer. Unit: Pascals
     */
    float getPressure() const {
        return _pressure;
    }

    /*
     * Get temperature from the Barometer. Unit: Celsius
     */
    float getTemperature() const {
        return _temperature;
    }

protected:
    float _temperature = 0;
    float _pressure = 0;
};

#endif //MRASV2_BAROMETER_H