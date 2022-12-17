//
// Created by Tom Danvers on 17/12/2022.
//

#include "Sensor_MS5607.h"
#include "system_messages/BarometerDataMsg.h"

int8_t Sensor_MS5607::setup() {
    log("Starting I2C bus");
    i2c_bus->begin();
    log("Starting up MS5607 barometer");
    bool result = read_PROM();
    if (!result) {
        log("Setup failure");
        return 1;
    } else {
        log("Setup success");
        return 0;
    }
}

int8_t Sensor_MS5607::loop() {

    uint32_t timeElapsed;

    switch (state) {
        case IDLE:
            // sensor is doing nothing, therefore we should start converting pressure
            i2c_bus->beginTransmission(i2c_address);
            i2c_bus->write(CONV_D1);
            if (i2c_bus->endTransmission() != 0) return 3;

            state = READING_PRESSURE;

            lastStateChange = millis();

            return 4;
        case READING_PRESSURE:
            timeElapsed = millis() - lastStateChange;

            // check that enough time was spent converting the measurement
            if (timeElapsed < CONV_Delay) return 1;

            // return status code 2 if ADC read fails and set state to idle
            if (!read_ADC(D1_pressure)) {
                state = IDLE;
                return 2;
            }


            // finished reading pressure, time to read temperature, so send conversion command
            i2c_bus->beginTransmission(i2c_address);
            i2c_bus->write(CONV_D2);
            if (i2c_bus->endTransmission() != 0) return 3;

            state = READING_TEMPERATURE;

            lastStateChange = millis();

            return 4;

        case READING_TEMPERATURE:
            timeElapsed = millis() - lastStateChange;

            // check that enough time was spent converting the measurement
            if (timeElapsed < CONV_Delay) return 1;

            // return status code 2 if ADC read fails and set state to idle
            if (!read_ADC(D2_temperature)) {
                state = IDLE;
                return 2;
            }

            state = IDLE;

            // This code is taken from the UravuLabs/MS5607 library
            dT = (float) D2_temperature - ((float) C5) * ((int) 1 << 8);
            OFF = (((int64_t) C2) * ((long) 1 << 17)) + dT * ((float) C4) / ((int) 1 << 6);
            SENS = ((float) C1) * ((long) 1 << 16) + dT * ((float) C3) / ((int) 1 << 7);
            float pa = (float) ((float) D1_pressure / ((long) 1 << 15));
            float pb = (float) (SENS / ((float) ((long) 1 << 21)));
            float pc = pa * pb;
            float pd = (float) (OFF / ((float) ((long) 1 << 15)));
            P = pc - pd;

            TEMP = 2000.0 + dT * ((float) C6) / (float) ((long) 1 << 23);

            // convert to correct units and shove into readable stores
            auto pressure = P;
            auto temperature = (float) TEMP / 100;

            // start reading pressure again
            i2c_bus->beginTransmission(i2c_address);
            i2c_bus->write(CONV_D1);
            if (i2c_bus->endTransmission() != 0) return 3;

            state = READING_PRESSURE;

            lastStateChange = millis();

            // publish the data
            auto baro_data_msg = new BarometerDataMsg();
            baro_data_msg->pressure = pressure;
            baro_data_msg->temperature = temperature;
            publish(baro_data_msg);
            break;
    }

    return 0;
}

bool Sensor_MS5607::reset() {
    log("Sending reset command");
    i2c_bus->beginTransmission(i2c_address);
    i2c_bus->write(MS5607_RESET); // reset command
    uint8_t error = i2c_bus->endTransmission();
    log("Reset command sent");
    if (error == 0) { // no error
        delay(3); // device takes 2.8ms to reload
        log("Reset successful");
        return true;
    }
    log("Reset failed: error code %d (see Wire.endTransmission())", error);
    return false;
}

bool Sensor_MS5607::read_PROM() {
    // reset the device before reading from the PROM
    if (!reset()) return false;

    // the PROM contains 8 total addresses of which 6 are calibration coefficients
    // address 0 corresponds to factory / setup data which we can ignore here
    // addresses 1-6 contain the coefficients which we are interested in
    // address 7 contains the serial code and CRC. We may wish to implement this CRC check in future
    if (!read_PROM_coefficient(MS5607_PROM_READ + 2, C1)) return false;
    if (!read_PROM_coefficient(MS5607_PROM_READ + 4, C2)) return false;
    if (!read_PROM_coefficient(MS5607_PROM_READ + 6, C3)) return false;
    if (!read_PROM_coefficient(MS5607_PROM_READ + 8, C4)) return false;
    if (!read_PROM_coefficient(MS5607_PROM_READ + 10, C5)) return false;
    if (!read_PROM_coefficient(MS5607_PROM_READ + 12, C6)) return false;

    log("PROM coefficients read successfully");
    log("C1: %d, C2: %d, C3: %d, C4: %d, C5: %d, C6: %d", C1, C2, C3, C4, C5, C6);
    return true;
}

bool Sensor_MS5607::read_PROM_coefficient(uint8_t command, uint16_t &store) {
    log("Sending PROM read command %x", command);
    // tell the device we wish to read from PROM
    i2c_bus->beginTransmission(i2c_address);
    i2c_bus->write(command);
    uint8_t error = i2c_bus->endTransmission();

    if (error != 0) {
        log("Error sending PROM read command %x", command);
        return false;
    }

    // request 2 bytes from the device
    // return false (error) if the amount of returned bytes does not equal 2
    uint8_t returned_bytes = i2c_bus->requestFrom(i2c_address, (uint8_t) 2);
    if (returned_bytes != 2) {
        log("Expected 2 bytes, but device returned %d. PROM read error.", returned_bytes);
        return false;
    };

    // datasheet quote:
    // "The command sequence is 8 bits long with a 16 bit result which is clocked with the MSB first"
    // and hence we read MSB first, then LSB
    uint8_t MSB = i2c_bus->read(); // most significant byte
    uint8_t LSB = i2c_bus->read(); // least significant byte

    log("PROM read %x successful. MSB: %x, LSB: %x", command, MSB, LSB);

    // convert to unsigned 16-bit integer and output to store (coefficients C1, C2, C3, etc)
    store = ((uint16_t) MSB) << 8 | (uint16_t) LSB;

    return true;
}

bool Sensor_MS5607::read_ADC(uint32_t &output) {
    uint8_t ADC_buffer[3];

    // read the pressure from the ADC
    i2c_bus->beginTransmission(i2c_address);
    i2c_bus->write(R_ADC);
    if (i2c_bus->endTransmission() != 0) return false;

    // we expect the device to return 3 bytes
    // which comprise the 24-bit result
    if (i2c_bus->requestFrom(i2c_address, (uint8_t) 3) != 3) return false;

    // read 3 bytes from ADC
    ADC_buffer[0] = i2c_bus->read();
    ADC_buffer[1] = i2c_bus->read();
    ADC_buffer[2] = i2c_bus->read();

    // convert result to 32 bit unsigned integer
    output = ((uint32_t) ADC_buffer[0]) << 16 | ((uint32_t) ADC_buffer[1]) << 8 | (uint32_t) ADC_buffer[2];

    return true;
}

void Sensor_MS5607::set_oversampling_ratio(uint16_t newOversamplingRatio) {
    OSR = newOversamplingRatio;
    switch (newOversamplingRatio) {
        case 256:
            CONV_D1 = 0x40;
            CONV_D2 = 0x50;
            CONV_Delay = 1;
            log("Oversampling ratio set to 256. Conversion delay set to 1ms");
            break;
        case 512:
            CONV_D1 = 0x42;
            CONV_D2 = 0x52;
            CONV_Delay = 2;
            log("Oversampling ratio set to 512. Conversion delay set to 2ms");
            break;
        case 1024:
            CONV_D1 = 0x44;
            CONV_D2 = 0x54;
            CONV_Delay = 3;
            log("Oversampling ratio set to 1024. Conversion delay set to 3ms");
            break;
        case 2048:
            CONV_D1 = 0x46;
            CONV_D2 = 0x56;
            CONV_Delay = 5;
            log("Oversampling ratio set to 2048. Conversion delay set to 5ms");
            break;
        case 4096:
            CONV_D1 = 0x48;
            CONV_D2 = 0x58;
            CONV_Delay = 10;
            log("Oversampling ratio set to 4096. Conversion delay set to 10ms");
            break;
        default:
            CONV_D1 = 0x48;
            CONV_D2 = 0x58;
            CONV_Delay = 10;
            log("Invalid OSR value entered - defaulting to 4096. Conversion delay set to 10ms");
            break;
    }
}
