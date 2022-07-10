//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_IMU_H
#define MRASV2_IMU_H

#include "Sensor.h"
#include "Vector.h"

class IMU : public Sensor {
public:
    /**
     * @return Current acceleration vector in ms^-2
     */
    Vector<float> getAcceleration() {
        return _acceleration;
    }

    /**
     * @return Current gyroscope vector in deg/s
     */
    Vector<float> getGyroVector() {
        return _gyro_vector;
    }

    Vector<float> getMagnetometerVector() {
        return _magnetometer_vector;
    }

protected:
    Vector<float> _acceleration{};
    Vector<float> _gyro_vector{};
    Vector<float> _magnetometer_vector{};
};

#endif //MRASV2_IMU_H
