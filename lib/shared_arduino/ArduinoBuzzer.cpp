// Written by Nikilesh Ramesh 09/03/2023

#include "ArduinoBuzzer.h"
#include "MRAS_Config.h"
#include "Arduino.h"
#include "system_messages/BuzzerMsg.h"


int8_t ArduinoBuzzer::setup() {
    log("Setting up buzzer");
    pinMode(buzzerPin, OUTPUT);

    _buzzer(NOTE_A6, 500, false);

    last_buzz = millis();

    return 0;
}

int8_t ArduinoBuzzer::loop() {

    if (ENABLE_BEEPING) {
        if (millis() - last_buzz > 1000) {
            _buzzer(NOTE_D7, 100, false);
            last_buzz = millis();
        }
    }

    return 0;
}

void ArduinoBuzzer::_buzzer(uint16_t frequency, uint32_t duration, bool block) {
    if (ENABLE_BUZZER) {
        tone(buzzerPin, frequency, duration);
    }
    if (block) {
        delay(duration);
    }
}

void ArduinoBuzzer::on_message(SystemMessage *msg) {
    if (msg->get_type() == BuzzerMsg_t) {
        BuzzerMsg *buzzerMsg = (BuzzerMsg *) msg;
        _buzzer(buzzerMsg->frequency, buzzerMsg->duration, buzzerMsg->block);
    }
}
