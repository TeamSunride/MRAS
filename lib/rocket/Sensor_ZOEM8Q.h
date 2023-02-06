//
// Created by robos on 23/12/2022.
//

#ifndef MRAS_SENSOR_ZOEM8Q_H
#define MRAS_SENSOR_ZOEM8Q_H


#include "Subsystem.h"
#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include <Arduino.h>
#include <Wire.h>
#include "SD.h"
#include <TimeLib.h>

#include "system_messages/GNSSDataMsg.h"


class Sensor_ZOEM8Q : public Subsystem{
private:
    SFE_UBLOX_GNSS *gnss{};
    TwoWire *_pipe;
    uint32_t _freq;
public:
    // Constructor
    Sensor_ZOEM8Q(uint8_t id, TwoWire& pipe, uint32_t freq) : Subsystem(id) {
        gnss = new SFE_UBLOX_GNSS();
        _pipe = &pipe;
        _freq = freq;
    }


    // Destructor
    ~Sensor_ZOEM8Q() {
        delete gnss;
    }

    int8_t setup() override;

    int8_t loop() override;

    void performOnlineAssist();

    SUBSYSTEM_NO_MESSAGE_HANDLER
    SUBSYSTEM_NAME("ZOEM8Q");


};

uint64_t getTimestampMillisGPS();

#endif //MRAS_SENSOR_ZOEM8Q_H
