//
// Created by robos on 12/04/2023.
//

#ifndef MRAS_SENSOR_UBLOX_M10S_H
#define MRAS_SENSOR_UBLOX_M10S_H


#include "Subsystem.h"
#include "SparkFun_u-blox_GNSS_v3.h"
#include <Arduino.h>
#include <Wire.h>
#include "SD.h"
#include <TimeLib.h>

#include "system_messages/GNSSDataMsg.h"

class Sensor_Ublox_GNSS : public Subsystem {
protected:
    SFE_UBLOX_GNSS *gnss{};
    TwoWire *_pipe;
    uint32_t _freq;
    uint8_t _navigationRate;
    const char *_name;
public:
    /**
     * @brief Construct a new Sensor_UBLOX_M10S object
     *
     * @param id The ID of the Subsystem
     * @param pipe The I2C bus to use
     * @param freq The frequency to use for the I2C bus
     * @param navigationRate The rate at which the module will output navigation data
     */
    Sensor_Ublox_GNSS(uint8_t id, TwoWire &pipe, uint32_t freq, uint32_t navigationRate, const char *name,
                      uint8_t gnss_id) : Subsystem(id) {
        gnss = new SFE_UBLOX_GNSS();
        _pipe = &pipe;
        _freq = freq;
        (navigationRate < 1) ? _navigationRate = 1 : _navigationRate = navigationRate;
        (navigationRate > 18) ? _navigationRate = 18
                              : _navigationRate = navigationRate; // max navigation frequency is 18 for M8Q
        _name = name;
        _gnss_id = gnss_id;
    }

    const char *get_name() override {
        return _name;
    }


    // Destructor
    ~Sensor_Ublox_GNSS() {
        delete gnss;
    }

    int8_t setup() override;

    int8_t loop() override;

    static uint16_t GPSweek();

    static uint32_t actualTimeOfWeekms();

    int8_t performOnlineAssist();

    SUBSYSTEM_NO_MESSAGE_HANDLER
    uint8_t _gnss_id;
};

uint64_t getTimestampMillisGPS();


#endif //MRAS_SENSOR_UBLOX_M10S_H