//
// Created by Tom Danvers on 19/11/2022.
//

#ifndef MRAS_IMU_LSM_LIS_H
#define MRAS_IMU_LSM_LIS_H

#include "IMU.h"
#include "LSM6DSO32.h"
#include "LIS3MDL.h"


class IMU_LSM_LIS : public IMU {
private:
    LSM6DSO32* lsm;
    LIS3MDL* lis;

public:
    int8_t begin() override;
    int8_t readData() override;

    explicit IMU_LSM_LIS(LSM6DSO32* _lsm, LIS3MDL* _lis) : lsm(_lsm), lis(_lis) {

    }
};


#endif //MRAS_IMU_LSM_LIS_H
