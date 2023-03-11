// Written by Nikilesh Ramesh -- 09/03/2023

#ifndef BUZZERINTERFACESYSTEM_H
#define BUZZERINTERFACESYSTEM_H

#include "Subsystem.h"
#include "BuzzerInterface.h"

class ArduinoBuzzer : public BuzzerInterface {
private:
    uint8_t buzzerPin = 0;

    uint32_t last_buzz = 0;
public:
    ArduinoBuzzer(uint8_t id, uint8_t pin) : BuzzerInterface(id) {
        buzzerPin = pin;
    };

    int8_t setup() override;

    int8_t loop() override;

    void _buzzer(uint16_t frequency, uint32_t duration, bool block) override;

    SUBSYSTEM_NO_MESSAGE_HANDLER;

    SUBSYSTEM_NAME("Buzzer");
};


#endif