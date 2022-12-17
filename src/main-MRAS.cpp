//
// Created by Tom Danvers on 05/12/2022.
//

#include <cstdio>

#include "MRAS_System.h"
#include "ArduinoTextLogger.h"
#include "FakeAccelerometer.h"
#include "NativeDataLogger.h"

TextLogger* logger = new ArduinoTextLogger(0, 115200);
MRAS_System* mras = MRAS_System::get_instance();

auto *accelerometer = new FakeAccelerometer(1);
auto *data_logger = new NativeDataLogger(2);

void setup() {
    mras->set_logger(logger);

    mras->add_subsystem(accelerometer);
    accelerometer->add_subscriber(data_logger);

    mras->setup();

    mras->loop();
}

void loop() {
    mras->loop();
    delay(100);
}