//
// Created by Tom Danvers on 18/12/2022.
//

#ifndef MRAS_SENSOR_ADXL375_H
#define MRAS_SENSOR_ADXL375_H


#include "Subsystem.h"
#include <SPI.h>
#include "ADXL375.h"

class Sensor_ADXL375 : public Subsystem {
private:
    ADXL375 *adxl;
public:
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
