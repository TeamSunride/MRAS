//
// Created by Tom Danvers on 01/01/2022.
// 2022 TeamSunride.
//

#include "I2CDevice.h"

I2CDevice::I2CDevice(byte i2c_address, TwoWire *i2c_pipe) {
    address = i2c_address;
    pipe = i2c_pipe;
}

byte I2CDevice::readRegister(byte offset) {
    pipe->beginTransmission(address);
    pipe->write(offset);
    pipe->endTransmission();

    byte numBytes = 1;
    byte result = 0;
    pipe->requestFrom(address, numBytes);
    while (pipe->available()) {
        result = pipe->read();
    }

    return result;
}

bool I2CDevice::writeRegister(byte offset, byte data) {
    pipe->beginTransmission(address);
    pipe->write(offset);
    pipe->write(data);
    return pipe->endTransmission() == 0; // 0 means success
}

void I2CDevice::readMultipleRegisters(uint8_t *outputPointer, uint8_t offset, uint8_t length) {
    uint8_t externalSpacePointer = 0;
    char c = 0;
    pipe->beginTransmission(address);
    pipe->write(offset);
    pipe->endTransmission();

    pipe->requestFrom(address, length);
    while (pipe->available() && (externalSpacePointer < length)) {
        c = pipe->read();
        *outputPointer = c;
        outputPointer++;
        externalSpacePointer++;
    }
}

bool I2CDevice::writeMultipleRegisters(byte *buffer, byte offset, byte length) {
    pipe->beginTransmission(address);
    pipe->write(offset);

    byte bytesWritten = 0;
    while (bytesWritten < length) {
        pipe->write(*buffer);
        buffer++;
        bytesWritten++;
    }
    return pipe->endTransmission() == 0; // 0 means success
}
