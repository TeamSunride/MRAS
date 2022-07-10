//
// Created by Tom Danvers on 10/07/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_ACCELEROMETER_ADXL375_H
#define MRASV2_ACCELEROMETER_ADXL375_H


#include "Accelerometer.h"
#include "I2CDevice.h"

class Accelerometer_ADXL375 : public Accelerometer, I2CDevice {
public:
    int8_t begin() override;

    int8_t readData() override;

    using I2CDevice::I2CDevice;
};


#endif //MRASV2_ACCELEROMETER_ADXL375_H
