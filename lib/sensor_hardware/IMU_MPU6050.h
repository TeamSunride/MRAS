//
// Created by tomto on 14/06/2022.
//

#ifndef MRAS_IMU_MPU6050_H
#define MRAS_IMU_MPU6050_H

#include "IMU.h"
#include "I2Cdev.h"
#include "MPU6050.h"

class IMU_MPU6050 : public IMU {
public:
    int8_t begin() override;
    int8_t readData() override;
private:
    MPU6050 mpu;
};


#endif //MRAS_IMU_MPU6050_H
