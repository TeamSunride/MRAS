// Written by Nikilesh Ramesh -- 09/03/2023

#ifndef BUZZERINTERFACESYSTEM_H
#define BUZZERINTERFACESYSTEM_H

#include "Subsystem.h"
#include "Subsystem.h"
#include "buzzer_notes.h"

class ArduinoBuzzer : public Subsystem {
private:
    uint8_t buzzerPin = 0;

    uint32_t last_buzz = 0;
    void _buzzer(uint16_t frequency, uint32_t duration, bool block);
public:
    ArduinoBuzzer(uint8_t id, uint8_t pin) : Subsystem(id) {
        buzzerPin = pin;
    };

    int8_t setup() override;

    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

    SUBSYSTEM_NAME("Buzzer");
};


#endif