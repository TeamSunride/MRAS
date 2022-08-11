//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#ifndef MRAS_IMU_H
#define MRAS_IMU_H

#include "Sensor.h"
#include "Vector.h"

class IMU : public Sensor {
public:
    /**
     * @return Current acceleration vector in ms^-2
     */
    Vector<float, 3> getAcceleration() {
        return _acceleration;
    }

    /**
     * @return Current gyroscope vector in deg/s
     */
    Vector<float, 3> getGyroVector() {
        return _gyro_vector;
    }

    Vector<float, 3> getMagnetometerVector() {
        return _magnetometer_vector;
    }

protected:
    Vector<float, 3> _acceleration {0,0,0};
    Vector<float, 3> _gyro_vector {0,0,0};
    Vector<float, 3> _magnetometer_vector {0,0,0};
};

#endif //MRAS_IMU_H
