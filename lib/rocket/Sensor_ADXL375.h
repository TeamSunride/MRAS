//
// Created by Tom Danvers on 18/12/2022.
//

#ifndef MRAS_SENSOR_ADXL375_H
#define MRAS_SENSOR_ADXL375_H


#include "Subsystem.h"
#include <SPI.h>
#include "ADXL375.h"

/**
 * @brief A subsystem for the ADXL375 accelerometer
 *
 * This Subsystem handles the setup and reading of data from the ADXL375 accelerometer.
 *
 * This Subsystem emits AccelerometerDataMsg messages to its subscribers.
 */
class Sensor_ADXL375 : public Subsystem {
private:
    ADXL375 *adxl;
public:
    /**
     * @brief Construct a new Sensor_ADXL375 object
     *
     * @param id The ID of the subsystem
     * @param chip_select The chip select pin for the ADXL375
     * @param spi The SPI object to use
     * @param frequency The frequency to use for the SPI bus
     */
    Sensor_ADXL375(uint8_t id, uint8_t chip_select, SPIClass &spi, uint32_t frequency) : Subsystem(id) {
        adxl = new ADXL375(chip_select, spi, frequency);
    }

    ~Sensor_ADXL375() {
        delete adxl;
    }

    int8_t setup() override;

    int8_t loop() override;

    SUBSYSTEM_NO_MESSAGE_HANDLER

    SUBSYSTEM_NAME("ADXL375")
};


#endif //MRAS_SENSOR_ADXL375_H
