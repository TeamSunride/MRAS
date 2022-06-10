//
// Created by Tom Danvers on 10/06/2022.
// 2022 TeamSunride.
//

#ifndef DART_GPIO_H
#define DART_GPIO_H

#include "Arduino.h"

#ifdef DART_PINS

#define BUZZER_PIN 37
#define RED_LED 15
#define BLUE_LED 6

void setup_GPIO() {
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(RED_LED, OUTPUT);
    pinMode(BLUE_LED, OUTPUT);
}

void playBuzzer(uint32_t duration) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(duration);
    digitalWrite(BUZZER_PIN, LOW);
}

void flashRedLED(uint32_t duration) {
    digitalWrite(RED_LED, HIGH);
    delay(duration);
    digitalWrite(RED_LED, LOW);
}

void flashBlueLED(uint32_t duration) {
    digitalWrite(BLUE_LED, HIGH);
    delay(duration);
    digitalWrite(BLUE_LED, LOW);
}

void toggleRedLED() {
    digitalWrite(RED_LED, !digitalRead(RED_LED));
}

void toggleBlueLED() {
    digitalWrite(BLUE_LED, !digitalRead(BLUE_LED));
}

#endif //DART_PINS
#endif //DART_GPIO_H
