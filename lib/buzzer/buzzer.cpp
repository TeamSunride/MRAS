//
// Created by Tom Danvers on 02/11/2022.
//
#include "buzzer.h"

void buzzer_tone(uint32_t frequency, uint32_t duration, bool block) {
    if (!MRAS_ENABLE_BUZZER) return;
    tone(BUZZER_PIN, frequency, duration);

    if (block) {
        delay(duration);
    }
}

void buzzer_startup() {
    buzzer_tone(1000, 100, true);
    buzzer_tone(1250, 100, true);
    buzzer_tone(1500, 600, true);
}

void buzzer_error() {
    buzzer_tone(600, 5000, false);
}

