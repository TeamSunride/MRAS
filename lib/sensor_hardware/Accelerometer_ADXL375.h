//
// Created by Tom Danvers on 24/07/2022.
// 2022 TeamSunride.
//

#ifndef MRAS_ACCELEROMETER_ADXL375_H
#define MRAS_ACCELEROMETER_ADXL375_H

#include "Accelerometer.h"
#include "protocol.h"

class Accelerometer_ADXL375 : public Accelerometer {
protected:
    protocol* device;
public:
    int8_t begin() override;
    int8_t readData() override;

    Accelerometer_ADXL375(TwoWire *pipe, int8_t address, uint32_t freq = 400000) {
        device = new I2CProtocol(address, pipe, freq);
    };

    // SPI constructor to be added in future when needed
};


#endif //MRAS_ACCELEROMETER_ADXL375_H