//
// Created by Tom Danvers on 06/04/2022.
// 2022 TeamSunride.
//

#ifndef MRAS_ACCELEROMETER_H
#define MRAS_ACCELEROMETER_H

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

#endif //MRAS_ACCELEROMETER_H
