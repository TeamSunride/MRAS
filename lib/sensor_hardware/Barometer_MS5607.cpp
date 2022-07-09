//
// Created by Tom Danvers on 05/04/2022.
// 2022 TeamSunride.
//

#include "Barometer_MS5607.h"

int8_t Barometer_MS5607::begin() {
    return readPROM() ? 0 : 1; // return 1 if readPROM fails
}

int8_t Barometer_MS5607::readData() {
    return 0;
}

bool Barometer_MS5607::reset() {
    pipe->beginTransmission(address);
    pipe->write(MS5607_RESET); // reset command
    uint8_t error = pipe->endTransmission();
    if (error == 0) { // no error
        delay(3); // device takes 2.8ms to reload
        return true;
    }

    Serial.println("Error: " + String(error, DEC));
    return false;
}

bool Barometer_MS5607::readPROM() {
    bool success =
            reset() && // reset the device before reading from PROM

            // the PROM contains 8 total addresses of which 6 are calibration coefficients
            // address 0 corresponds to factory / setup data which we can ignore here
            // addresses 1-6 contain the coefficients which we are interested in
            // address 7 contains the serial code and CRC. We may wish to implement this CRC check in future
            readPROMCoefficient(MS5607_PROM_READ + 2, C1) &&
            readPROMCoefficient(MS5607_PROM_READ + 4, C2) &&
            readPROMCoefficient(MS5607_PROM_READ + 6, C3) &&
            readPROMCoefficient(MS5607_PROM_READ + 8, C4) &&
            readPROMCoefficient(MS5607_PROM_READ + 10, C5) &&
            readPROMCoefficient(MS5607_PROM_READ + 12, C6);

    if (success) {
        Serial.println("MS5607 PROM Calibration Coefficients:");
        Serial.println("C1: " + String(C1));
        Serial.println("C2: " + String(C2));
        Serial.println("C3: " + String(C3));
        Serial.println("C4: " + String(C4));
        Serial.println("C5: " + String(C5));
        Serial.println("C6: " + String(C6));
    } else {
        Serial.println("Error when reading PROM coefficients");
    }

    return success;
}

bool Barometer_MS5607::readPROMCoefficient(byte command, uint16_t &store) {
    // tell the device we wish to read from PROM
    pipe->beginTransmission(address);
    pipe->write(command);
    uint8_t error = pipe->endTransmission();

    if (error != 0) return false;

    // request 2 bytes from the device
    // return false (error) if the amount of returned bytes does not equal 2
    if (pipe->requestFrom(address, (uint8_t) 2) != 2) return false;

    // datasheet quote:
    // "The command sequence is 8 bits long with a 16 bit result which is clocked with the MSB first"
    // and hence we read MSB first, then LSB
    uint8_t MSB = pipe->read(); // most significant byte
    uint8_t LSB = pipe->read(); // least significant byte

    // convert to unsigned 16-bit integer and output to store (coefficients C1, C2, C3, etc)
    store = ((uint16_t) MSB) << 8 | (uint16_t) LSB;

    return true;
}

Barometer_MS5607::Barometer_MS5607(byte i2c_address, TwoWire *i2c_pipe) {
    address = i2c_address;
    pipe = i2c_pipe;
}


