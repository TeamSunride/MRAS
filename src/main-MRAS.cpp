//
// Created by Tom Danvers on 05/12/2022.
//

#include <cstdio>

#include "MRAS_System.h"
#include "ArduinoTextLogger.h"

TextLogger* logger = new ArduinoTextLogger(0, 115200);
MRAS_System* mras = MRAS_System::get_instance();

void setup() {
    mras->set_logger(logger);
    mras->setup();
}

void loop() {

    mras->loop();
    delay(100);

}