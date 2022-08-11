//
// Created by Tom Danvers on 10/07/2022.
// 2022 TeamSunride.
//

#ifndef MRAS_ACCELEROMETER_ADXL375_OLD_H
#define MRAS_ACCELEROMETER_ADXL375_OLD_H


#include "Accelerometer.h"
#include "I2CDevice.h"

class Accelerometer_ADXL375_OLD : public Accelerometer, I2CDevice {
public:
    int8_t begin() override;

    int8_t readData() override;

    using I2CDevice::I2CDevice;
};


#endif //MRAS_ACCELEROMETER_ADXL375_OLD_H
