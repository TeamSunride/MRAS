//
// Created by Tom Danvers on 05/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_BAROMETER_MS5607_H
#define MRASV2_BAROMETER_MS5607_H

#include <cstdint>
#include <Wire.h>
#include "Barometer.h"

#define MS5607_RESET 0x1E
#define MS5607_PROM_READ 0xA0

class Barometer_MS5607 : public Barometer {
public:
    int8_t begin() override;

    int8_t readData() override;


    Barometer_MS5607(byte i2c_address, TwoWire *i2c_pipe);
#ifndef MS5607_GODMODE
private:
#endif
    byte address;
    TwoWire *pipe;
    uint16_t OSR = 256;

    // calibration coefficients
    // initialising them all separately looks ugly yes
    uint16_t C1 = 0;
    uint16_t C2 = 0;
    uint16_t C3 = 0;
    uint16_t C4 = 0;
    uint16_t C5 = 0;
    uint16_t C6 = 0;


    /**
     * The Reset sequence shall be sent once after power-on to make sure that the calibration PROM gets loaded into
        the internal register. It can be also used to reset the device ROM from an unknown condition
     * @return Whether
     */
    bool reset();

    /**
     * The read command for PROM shall be executed once after reset by the user to read the content of the calibration
     * PROM and to calculate the calibration coefficients. There are in total 8 addresses resulting in a total memory
     * of 128 bit. Address 0 contains factory data and the setup, addresses 1-6 calibration coefficients and
     * address 7 contains the serial code and CRC. The command sequence is 8 bits long with a 16 bit result which is
     * clocked with the MSB first.
     * @return True if the operation was successful, otherwise False
     */
    bool readPROM();

    /**
     * Used by readPROM to read each PROM coefficient
     * @param command The command to set the sensor into PROM read mode, corresponding to the correct coefficient
     * @param store The location to store the resulting coefficient
     * @return True if the operation was a success, otherwise False
     */
    bool readPROMCoefficient(byte command, uint16_t& store);

};


#endif //MRASV2_BAROMETER_MS5607_H
