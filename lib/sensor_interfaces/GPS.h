//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#ifndef MRAS_GPS_H
#define MRAS_GPS_H

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

    uint8_t getSatellitesInView() const {
        return _satellites_in_view;
    }

    uint8_t getFixType() const {
        return _fix_type;
    }

protected:
    float _latitude = 0;
    float _longitude = 0;
    float _altitude = 0;
    uint8_t _satellites_in_view = 0;

    /*
     * The fix type is as follows:
    0 = no fix
    1 = dead reckoning (requires external sensors)
    2 = 2D (not quite enough satellites in view)
    3 = 3D (the standard fix)
    4 = GNSS + dead reckoning (requires external sensors)
    5 = Time fix only
     */
    uint8_t _fix_type = 0;
};

#endif //MRAS_GPS_H
