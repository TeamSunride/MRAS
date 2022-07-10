//
// Created by Tom Danvers on 01/01/2022.
// 2022 TeamSunride.
//

#ifndef I2CDEVICE_H
#define I2CDEVICE_H

#include "Wire.h"

class I2CDevice {
public:
    I2CDevice(byte i2c_address, TwoWire *i2c_pipe);
    byte readRegister(byte offset);
    bool writeRegister(byte offset, byte data);
    void readMultipleRegisters(byte *outputPointer, byte offset, byte length);
    bool writeMultipleRegisters(byte *buffer, byte offset, byte length);
protected:
    byte address;
    TwoWire *pipe;
};


#endif //I2CDEVICE_H
