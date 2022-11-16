//
// Created by Tom Danvers on 02/11/2022.
//

#ifndef MRAS_BUZZER_H
#define MRAS_BUZZER_H

#include "Arduino.h"

#ifdef GS_V1_PINS
#define BUZZER_PIN A5
#elif DART_PINS
#define BUZZER_PIN 37
#endif

#define MRAS_ENABLE_BUZZER true
#define MRAS_ENABLE_BEEPING false

void buzzer_tone(uint32_t frequency, uint32_t duration, bool block=false);

void buzzer_startup();

void buzzer_error();

#endif //MRAS_BUZZER_H
