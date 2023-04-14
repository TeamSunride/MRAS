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

class Sensor_UBLOX_M10S : public Subsystem {
private:
    SFE_UBLOX_GNSS *gnss{};
    TwoWire *_pipe;
    uint32_t _freq;
    uint8_t _navigationRate;
public:
    /**
     * @brief Construct a new Sensor_UBLOX_M10S object
     *
     * @param id The ID of the Subsystem
     * @param pipe The I2C bus to use
     * @param freq The frequency to use for the I2C bus
     * @param navigationRate The rate at which the module will output navigation data
     */
    Sensor_UBLOX_M10S(uint8_t id, TwoWire& pipe, uint32_t freq, uint32_t navigationRate) : Subsystem(id) {
            gnss = new SFE_UBLOX_GNSS();
            _pipe = &pipe;
            _freq = freq;
            (navigationRate < 1 ) ? _navigationRate = 1 : _navigationRate = navigationRate;
            (navigationRate > 18) ? _navigationRate = 18 : _navigationRate = navigationRate; // max navigation frequency is 18 for M8Q
    }


    // Destructor
    ~Sensor_UBLOX_M10S() {
        delete gnss;
    }

    int8_t setup() override;

    int8_t loop() override;

    static uint16_t GPSweek();

    static uint32_t actualTimeOfWeekms();

    int8_t performOnlineAssist();

    SUBSYSTEM_NO_MESSAGE_HANDLER
    SUBSYSTEM_NAME("Sensor_UBLOX_M10S");


};

uint64_t getTimestampMillisGPS();


#endif //MRAS_SENSOR_UBLOX_M10S_H
