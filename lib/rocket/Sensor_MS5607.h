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

/**
Sensor_MS5607 class is a C++ driver for the MS5607 barometric pressure sensor. It is a child class of the Subsystem base class and is responsible for communicating with the sensor over I2C, reading and interpreting the sensor's data, and providing that data to the system.

##High-level Overview:
The `setup()` method initializes the I2C bus and reads the sensor's calibration coefficients from its PROM (Programmable Read-Only Memory). It returns 0 on success and a non-zero value on failure.

The `loop()` method reads pressure and temperature data from the sensor. It uses a finite state machine to control the timing of the pressure and temperature measurements. It returns different status codes depending on the state of the sensor and the outcome of the measurements.

The class has several private variables, such as the i2c address of the sensor, the i2c bus object, and the sensor's calibration coefficients. It also has several private constants, such as the OSR (Oversampling Ratio), which determines the resolution of the sensor's measurements, and the CONV_D1, CONV_D2, and CONV_Delay constants, which determine the timing of the pressure and temperature measurements.

##Step by step process for how data is read from the sensor:
1. In the setup() method, the I2C bus is initialized and the read_PROM() method is called to read the sensor's calibration coefficients from its PROM.
2. In the loop() method, a switch case statement is used to determine the current state of the sensor, and based on that, the appropriate action is taken.
3. If the state is IDLE, a command is sent to the sensor to start converting pressure measurement.
4. After sending the command, the state is set to READING_PRESSURE and the time at which the state was changed is recorded.
5. The program then waits for the conversion delay.
6. After the delay, the `read_ADC()` method is called to read the digital value of the pressure measurement from the sensor's ADC (Analog-to-Digital Converter).
7. If the reading is successful, the state is changed to READING_TEMPERATURE and a similar process is followed to read the temperature measurement.
8. The read values are then used to calculate the temperature and pressure using the sensor's calibration coefficients and a mathematical formula, taking into account the sensor's OSR value.
 */
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

    float dT{}, TEMP{}, P{};
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
    Sensor_MS5607(uint8_t id, byte i2c_address, TwoWire &i2c_bus) : Subsystem(id), i2c_address(i2c_address),
                                                                    i2c_bus(&i2c_bus) {};

    int8_t setup() override;

    int8_t loop() override;

    SUBSYSTEM_NO_MESSAGE_HANDLER

    SUBSYSTEM_NAME("MS5607")
};


#endif //MRAS_SENSOR_MS5607_H
