//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_IMU_H
#define MRASV2_IMU_H

#include "Sensor.h"
#include "Vector3D.h"

class IMU : public Sensor {
public:
    Vector3D getAcceleration() {
        return _acceleration;
    }

    Vector3D getGyroVector() {
        return _gyro_vector;
    }

    Vector3D getMagnetometerVector() {
        return _magnetometer_vector;
    }
private:
    Vector3D _acceleration{};
    Vector3D _gyro_vector{};
    Vector3D _magnetometer_vector{};
};

#endif //MRASV2_IMU_H
