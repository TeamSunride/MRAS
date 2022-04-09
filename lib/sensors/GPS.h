//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_GPS_H
#define MRASV2_GPS_H

#include "Sensor.h"

class GPS : public Sensor {
public:
    float getLatitude() const {
        return _latitude;
    }

    float getLongitude() const {
        return _longitude;
    }

    float getAltitude() const {
        return _altitude;
    }

    float getSpeed() const {
        return _speed;
    }

    int16_t getSatellitesInView() const {
        return _satellites_in_view;
    }

private:
    float _latitude = 0;
    float _longitude = 0;
    float _altitude = 0;
    float _speed = 0;
    int16_t _satellites_in_view = 0;
};

#endif //MRASV2_GPS_H
