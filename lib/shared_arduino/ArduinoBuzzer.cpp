// Written by Nikilesh Ramesh 09/03/2023

#include "ArduinoBuzzer.h"

#include "Arduino.h"


int8_t ArduinoBuzzer::setup() {
    log("Setting up buzzer");
    pinMode(buzzerPin, OUTPUT);
    return 0;
}

int8_t ArduinoBuzzer::loop() { return 0; }

void ArduinoBuzzer::_buzzer(uint16_t frequency, uint32_t duration) {
    tone(buzzerPin, frequency, duration);
}