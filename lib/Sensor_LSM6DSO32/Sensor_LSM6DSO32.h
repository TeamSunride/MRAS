//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_SENSOR_LSM6DSO32_H
#define MRAS_SENSOR_LSM6DSO32_H


#include "Subsystem.h"
#include "LSM6DSO32.h"
#include "Arduino.h"
#include "SPI.h"

#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/GyroDataMsg.h"

class Sensor_LSM6DSO32 : public Subsystem {
private:
    LSM6DSO32 *lsm;
public:
    Sensor_LSM6DSO32(uint8_t id, uint8_t chip_select, SPIClass &spi, uint32_t frequency) : Subsystem(id) {
        lsm = new LSM6DSO32(chip_select, spi, frequency);
    }

    ~Sensor_LSM6DSO32() {
        delete lsm;
    }

    int8_t setup() override;

    int8_t loop() override;

    const char *get_name() override {
        return "LSM6DSO32";
    }

    void on_message(SystemMessage *msg) override {};
};


#endif //MRAS_SENSOR_LSM6DSO32_H
