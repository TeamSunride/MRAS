//
// Created by Tom Danvers on 19/11/2022.
//

#include "IMU_LSM_LIS.h"

int8_t IMU_LSM_LIS::begin() {
    lis->begin();
    lis->default_configuration();


    lsm->begin();
    lsm->default_configuration();

    lsm->set_accel_ODR(ODR_6667_HZ);
    lsm->set_gyro_ODR(ODR_6667_HZ);
    lis->set_mag_ODR(ODR_1000_HZ);

    return 0;
}

int8_t IMU_LSM_LIS::readData() {
    _acceleration = (Vector<float, 3>) lsm->get_accel();
    _gyro_vector = (Vector<float, 3>) lsm->get_gyro();
    _magnetometer_vector = (Vector<float, 3>) lis->get_mag();
    return 0;
}
