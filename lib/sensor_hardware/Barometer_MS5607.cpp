//
// Created by Tom Danvers on 05/04/2022.
// 2022 TeamSunride.
//

#include "Barometer_MS5607.h"
#include "Int64String.h"

int8_t Barometer_MS5607::begin() {
    return readPROM() ? 0 : 1; // return 1 if readPROM fails
}

/*
 * This function assumes that is called once per loop. In order to get up-to-date pressure and temperature values,
 *  you must call this function as frequently as possible
 *
 * This is the only way to achieve non-blocking operation with the MS5607.
 *
 * STATUS CODES:
 * 0 - a full read was completed (requires multiple calls of readData() to do this)
 * 1 - sensor is still converting the measurement
 * 2 - ADC read failed
 * 3 - error sending conversion command
 * 4 - the operation was a success, but readData() must be called again to finish converting the measurement
 */
int8_t Barometer_MS5607::readData() {

    uint32_t timeElapsed;

    switch (state) {
        case IDLE:
            // sensor is doing nothing, therefore we should start converting pressure
            pipe->beginTransmission(address);
            pipe->write(CONV_D1);
            if (pipe->endTransmission() != 0) return 3;

            state = READING_PRESSURE;

            lastStateChange = millis();

            return 4;
        case READING_PRESSURE:
            timeElapsed = millis() - lastStateChange;

            // check that enough time was spent converting the measurement
            if (timeElapsed < CONV_Delay) return 1;

            // return status code 2 if ADC read fails and set state to idle
            if (!readADC(D1_pressure)) {
                state = IDLE;
                return 2;
            }


            // finished reading pressure, time to read temperature, so send conversion command
            pipe->beginTransmission(address);
            pipe->write(CONV_D2);
            if (pipe->endTransmission() != 0) return 3;

            state = READING_TEMPERATURE;

            lastStateChange = millis();

            return 4;

        case READING_TEMPERATURE:
            timeElapsed = millis() - lastStateChange;

            // check that enough time was spent converting the measurement
            if (timeElapsed < CONV_Delay) return 1;

            // return status code 2 if ADC read fails and set state to idle
            if (!readADC(D2_temperature)) {
                state = IDLE;
                return 2;
            }

            state = IDLE;

            // we must now convert D1 and D2 to meaningful values
            // refer to page 8 on the datasheet
            dT = (float) D2_temperature - (float) C5 * 256;
            TEMP = (float) (2000 + dT * (C6 / 8388608.0)); // a value of 2000 corresponds to 20 degrees C

            // calculate temperature compensated pressure
            OFF = ((int64_t) C2 * ((int64_t) 1 << 17)) + (int64_t) (((float) C4 * dT) / (1 << 6));
            SENS = ((int64_t) C1 * (1 << 16)) + (int64_t) (((float)C3 * dT) / (1 << 17));
            P = (int32_t) (((int64_t) D1_pressure * (SENS / (1<<21)) - OFF) / ((int64_t) 1 << 15)); // 110002 = 1100.02 mbar

            /*
            Serial.println("dT: " + String(dT));
            Serial.println("TEMP: " + String(TEMP));
            Serial.println("OFF: " + int64String(OFF));
            Serial.println("SENS: " + int64String(SENS));
            Serial.println("P: " + String(P));
            */

            // convert to correct units and shove into readable stores
            _pressure = (float) P / 100;
            _temperature = (float) TEMP / 100;

            // start reading pressure again
            pipe->beginTransmission(address);
            pipe->write(CONV_D1);
            if (pipe->endTransmission() != 0) return 3;

            state = READING_PRESSURE;

            lastStateChange = millis();
            break;
    }

    return 0;
}

bool Barometer_MS5607::readADC(uint32_t &output) {
    uint8_t ADC_buffer[3];

    // read the pressure from the ADC
    pipe->beginTransmission(address);
    pipe->write(R_ADC);
    if (pipe->endTransmission() != 0) return false;

    // we expect the device to return 3 bytes
    // which comprise the 24-bit result
    if (pipe->requestFrom(address, (uint8_t) 3) != 3) return false;

    // read 3 bytes from ADC
    ADC_buffer[0] = pipe->read();
    ADC_buffer[1] = pipe->read();
    ADC_buffer[2] = pipe->read();

    // convert result to 32 bit unsigned integer
    output = ((uint32_t) ADC_buffer[0]) << 16 | ((uint32_t) ADC_buffer[1]) << 8 | (uint32_t) ADC_buffer[2];

    return true;
}

bool Barometer_MS5607::reset() {
    pipe->beginTransmission(address);
    pipe->write(MS5607_RESET); // reset command
    uint8_t error = pipe->endTransmission();
    if (error == 0) { // no error
        delay(3); // device takes 2.8ms to reload
        return true;
    }

    Serial.println("MS5607 reset error: " + String(error, DEC));
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

void Barometer_MS5607::setOversamplingRatio(uint16_t newOversamplingRatio) {
    OSR = newOversamplingRatio;
    switch (newOversamplingRatio) {
        case 256:
            CONV_D1 = 0x40;
            CONV_D2 = 0x50;
            CONV_Delay = 1;
            break;
        case 512:
            CONV_D1 = 0x42;
            CONV_D2 = 0x52;
            CONV_Delay = 2;
            break;
        case 1024:
            CONV_D1 = 0x44;
            CONV_D2 = 0x54;
            CONV_Delay = 3;
            break;
        case 2048:
            CONV_D1 = 0x46;
            CONV_D2 = 0x56;
            CONV_Delay = 5;
            break;
        case 4096:
            CONV_D1 = 0x48;
            CONV_D2 = 0x58;
            CONV_Delay = 10;
            break;
        default:
            CONV_D1 = 0x40;
            CONV_D2 = 0x50;
            CONV_Delay = 1;
            break;
    }
}



