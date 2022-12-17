//
// Created by Tom Danvers on 05/12/2022.
//

#include "Arduino.h"

void setup() {
    Serial.begin(9600);
}

void loop() {
    Serial.print("I am alive!");
}