//
// Created by Tom Danvers on 10/07/2022.
// 2022 TeamSunride.
//

#include "Accelerometer_ADXL375.h"

#define ADXL375_SCALE_FACTOR 0.049f
#define GRAVITY 9.81f

int8_t Accelerometer_ADXL375::begin() {
    // device ID should equal 0xE5
    if (readRegister(0x00) != 0xE5) return 1;

    // set output data rate to 800Hz
    if (!writeRegister(0x2C, 0b1101)) return 2;

    // set data format to MSB first
    // if (!writeRegister(0x31, 0b100)) return 3;

    // tell device to enter "measure" mode
    if (!writeRegister(0x2D, 0b1000)) return 4;


    return 0;
}

int8_t Accelerometer_ADXL375::readData() {
    uint8_t buffer[6];
    memset(buffer, 0, sizeof buffer);

    readMultipleRegisters(buffer, 0x32, 6);

    int16_t x = ((int16_t) buffer[0]) | (((int16_t) buffer[1]) << 8);
    int16_t y = ((int16_t) buffer[2]) | (((int16_t) buffer[3]) << 8);
    int16_t z = ((int16_t) buffer[4]) | (((int16_t) buffer[5]) << 8);

    _acceleration[0] = (float) x;
    _acceleration[1] = (float) y;
    _acceleration[2] = (float) z;

    _acceleration = (_acceleration * ADXL375_SCALE_FACTOR) / GRAVITY;

    return 0;
}
