//
// Created by Tom Danvers on 24/04/2022.
// 2022 TeamSunride.
// This file runs if built with the "ground" environment
//

#include "Arduino.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.println("this is the ground station!");
    delay(1000);
}
