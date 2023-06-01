//
// Created by Tom Danvers on 12/12/2022.
//

#include <cstdio>

#include "MRAS_System.h"
#include "NativeTextLogger.h"
#include "FakeAccelerometer.h"


int main() {
    TextLogger* logger = new NativeTextLogger(0);
    MRAS_System* mras = MRAS_System::get_instance();

    auto *accelerometer = new FakeAccelerometer(1);

    mras->set_logger(logger);

    mras->add_subsystem(accelerometer);

    mras->setup();

    mras->loop();

    return 0;
}