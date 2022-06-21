//
// Created by tomto on 14/06/2022.
//

#include "IMU_MPU6050.h"

// class reference:
// https://www.i2cdevlib.com/docs/html/class_m_p_u6050.html#a8fc7eab1302281f6e4bc953379f3237b

int8_t IMU_MPU6050::begin() {
    // assume that WIre.begin() was already called somewhere.

    mpu.initialize();
    mpu.setFullScaleAccelRange(3); // +- 16G
    mpu.setFullScaleGyroRange(3); // +- 2000 deg/s

    Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");

    return 0;
}

int8_t IMU_MPU6050::readData() {
    int16_t ax, ay, az;
    int16_t gx, gy, gz;

    mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
    _acceleration.setX(ax);
    _acceleration.setY(ay);
    _acceleration.setZ(az);
    _gyro_vector.setX(gx);
    _gyro_vector.setY(gy);
    _gyro_vector.setZ(gz);
    return 0;
}
