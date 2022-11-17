//
// Created by Tom Danvers on 24/07/2022.
// 2022 TeamSunride.
//

#include "Accelerometer_ADXL375.h"

int8_t Accelerometer_ADXL375::begin() {
    device->protocol_begin();

    uint8_t deviceID = device->read_reg(0x00);

    // device ID should equal 0xE5
    if (deviceID != 0xE5) return 1;

    // put device in standby mode
    if (device->write_reg(0x2D, 0b0000) != 0) return 5;

    // set output data rate to 400Hz
    if (device->write_reg(0x2C, 0b1100) != 0) return 2;

    // fix range of device https://github.com/adafruit/Adafruit_ADXL375/issues/1
    if (device->write_reg(0x31, 0b00001011) != 0) return 3;

    // tell device to enter "measure" mode
    if (device->write_reg(0x2D, 0b1000) != 0) return 4;

    Serial.println("ADXL375 DATA_FORMAT register:");
    Serial.println(device->read_reg(0x31), BIN);
    Serial.println("===========");

    return 0;
}

int8_t Accelerometer_ADXL375::readData() {
    uint8_t buffer[6];
    memset(buffer, 0, sizeof buffer);

    device->read_regs(0x32, buffer, 6);



    Vector<int16_t, 3> rawAccel = {
            (int16_t) ((uint16_t)buffer[1] << 8 | ((uint16_t)buffer[0])),
            (int16_t) ((uint16_t)buffer[3] << 8 | (uint16_t)buffer[2]),
            (int16_t) ((uint16_t)buffer[5] << 8 | (uint16_t)buffer[4])
    };



    _acceleration = (((Vector<float, 3>) rawAccel) * 0.00981 * 49);

    /*
    for (uint8_t registerValue : buffer) {
        Serial.println(registerValue, BIN);
    }

    Serial.println("Raw axis data: ");
    for (auto axis : {rawAccel[0], rawAccel[1], rawAccel[2]}) {
        Serial.println(axis);
    }

    for (auto axis : {_acceleration[0], _acceleration[1], _acceleration[2]}) {
        Serial.print(axis);
        Serial.print(", ");
    }
    Serial.println("");
     */


    return 0;
}
