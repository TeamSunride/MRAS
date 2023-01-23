//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_SENSOR_LIS3MDL_H
#define MRAS_SENSOR_LIS3MDL_H


#include "Subsystem.h"
#include "Arduino.h"
#include "SPI.h"
#include "LIS3MDL.h"
#include "system_messages/MagnetometerDataMsg.h"

class Sensor_LIS3MDL : public Subsystem {
private:
    LIS3MDL *lis;
public:
    Sensor_LIS3MDL(uint8_t id, uint8_t chip_select,
                   SPIClass &spi, uint32_t frequency)
                   : Subsystem(id) {
        lis = new LIS3MDL(chip_select, spi, frequency);
    }

    ~Sensor_LIS3MDL() {
        delete lis;
    }

    int8_t setup() override;

    int8_t loop() override;

    SUBSYSTEM_NAME("LIS3MDL")
    SUBSYSTEM_NO_MESSAGE_HANDLER
};


#endif //MRAS_SENSOR_LIS3MDL_H
