//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_SIMULINKDATALOGGER_H
#define MRAS_SIMULINKDATALOGGER_H


#include "Subsystem.h"


typedef union{
    float number;
    uint8_t bytes[4];
} FLOATUNION_t;

/**
 * @brief A subsystem that logs SystemMessages using its log() function, for Simulink
 */
class SimulinkDataLogger: public Subsystem {
public:
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;

    void on_message(SystemMessage *msg) override;
    float getFloat();

    SUBSYSTEM_NAME("SimulinkDataLogger")
private:
    FLOATUNION_t position;
    FLOATUNION_t velocity;
    FLOATUNION_t pressure;
    FLOATUNION_t yAccel;
};


#endif //MRAS_NATIVEDATALOGGER_H
