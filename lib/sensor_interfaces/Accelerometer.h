//
// Created by Tom Danvers on 06/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_ACCELEROMETER_H
#define MRASV2_ACCELEROMETER_H

#include "Sensor.h"
#include "Vector.h"

class Accelerometer : public Sensor {
public:
    Vector<float, 3> getAcceleration() {
        return _acceleration;
    }

protected:
    Vector<float, 3>  _acceleration{};
};

#endif //MRASV2_ACCELEROMETER_H
