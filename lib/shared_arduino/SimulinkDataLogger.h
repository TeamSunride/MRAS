//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_SIMULINKDATALOGGER_H
#define MRAS_SIMULINKDATALOGGER_H


#include "Subsystem.h"
#include "Arduino.h"
#include "system_messages/OrientationDataMsg.h"

typedef union{
    float number;
    uint8_t bytes[4];
} FLOATUNION_t;

/**
 * @brief A subsystem that logs SystemMessages using its log() function, for Simulink
 */
class SimulinkDataLogger: public Subsystem {
public:
    SimulinkDataLogger(uint8_t id, uint8_t mode, long baud) : Subsystem(id) {
        Serial.begin(baud);
        while (!Serial) {
            delay(1);
        }
        _mode = mode;
    };
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;


    void on_message(SystemMessage *msg) override;
    static float getFloat();

    SUBSYSTEM_NAME("SimulinkDataLogger")
private:
    FLOATUNION_t position;
    FLOATUNION_t velocity;
    FLOATUNION_t pressure;
    FLOATUNION_t yAccel;
    FLOATUNION_t gyroX;
    FLOATUNION_t gyroY;
    FLOATUNION_t gyroZ;
    FLOATUNION_t q1;
    FLOATUNION_t q2;
    FLOATUNION_t q3;
    FLOATUNION_t q4;

    uint8_t _mode;
};

#endif //MRAS_SIMULINKDATALOGGER_H