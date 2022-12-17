//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_SENSOR_MS5607_H
#define MRAS_SENSOR_MS5607_H


#include <Wire.h>
#include "Subsystem.h"

#define MS5607_RESET 0x1E
#define MS5607_PROM_READ 0xA0
#define R_ADC  0X00

class Sensor_MS5607 : public Subsystem {
private:
    uint8_t i2c_address;
    TwoWire *i2c_bus;

    uint16_t OSR = 4096;     // default oversampling ratio
    uint8_t CONV_D1 = 0x48;   // corresponding pressure conv. command for OSR
    uint8_t CONV_D2 = 0x58;   // corresponding temp conv. command for OSR
    uint8_t CONV_Delay = 10;   // corresponding conv. delay for OSR

    // calibration coefficients
    // initialising them all separately looks ugly yes
    uint16_t C1 = 0;
    uint16_t C2 = 0;
    uint16_t C3 = 0;
    uint16_t C4 = 0;
    uint16_t C5 = 0;
    uint16_t C6 = 0;

    uint32_t D1_pressure{};
    uint32_t D2_temperature{};

    float dT{}, TEMP{};
    int32_t P{};
    int64_t OFF{}, SENS{};

    uint32_t lastStateChange = 0;


    enum {
        IDLE,
        READING_PRESSURE,
        READING_TEMPERATURE
    } state = IDLE;

    /**
     * The read command for PROM shall be executed once after reset by the user to read the content of the calibration
     * PROM and to calculate the calibration coefficients. There are in total 8 addresses resulting in a total memory
     * of 128 bit. Address 0 contains factory data and the setup, addresses 1-6 calibration coefficients and
     * address 7 contains the serial code and CRC. The command sequence is 8 bits long with a 16 bit result which is
     * clocked with the MSB first.
     * @return True if the operation was successful, otherwise False
     */
    bool read_PROM();

    /**
     * Used by readPROM to read each PROM coefficient
     * @param command The command to set the sensor into PROM read mode, corresponding to the correct coefficient
     * @param store The location to store the resulting coefficient
     * @return True if the operation was a success, otherwise False
     */
    bool read_PROM_coefficient(uint8_t command, uint16_t &store);

    /**
     * The Reset sequence shall be sent once after power-on to make sure that the calibration PROM gets loaded into
     * the internal register. It can be also used to reset the device ROM from an unknown condition
     * @return Success (true/false)
     */
    bool reset();

    /**
     * Change the oversampling ratio of the sensor.
     *
     * High OSR corresponds to improved resolution but longer conversion times
     * @param newOversamplingRatio Possible values: 256, 512, 1024, 2048, 4096
     *
     * Default OSR is 4096
     */
    void set_oversampling_ratio(uint16_t newOversamplingRatio);

    /**
     * Internal method to read the result from the ADC after conversion.
     * @param output 32-bit unsigned integer variable to write result to
     * @return True if the operation was successful, otherwise false
     */
    bool read_ADC(uint32_t &output);

public:
    Sensor_MS5607(uint8_t id, byte i2c_address, TwoWire *i2c_bus) : Subsystem(id), i2c_address(i2c_address),
                                                                    i2c_bus(i2c_bus) {};

    int8_t setup() override;

    int8_t loop() override;

    SUBSYSTEM_NO_MESSAGE_HANDLER

    SUBSYSTEM_NAME("MS5607")
};


#endif //MRAS_SENSOR_MS5607_H
