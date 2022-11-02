//
// Created by Tom Danvers on 02/11/2022.
//

#ifndef MRAS_BUZZER_H
#define MRAS_BUZZER_H

#include "Arduino.h"

#define BUZZER_PIN A5

void buzzer_tone(uint32_t frequency, uint32_t duration, bool block=false);

void buzzer_startup();

void buzzer_error();

#endif //MRAS_BUZZER_H
