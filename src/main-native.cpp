//
// Created by Tom Danvers on 12/12/2022.
//

#include <cstdio>

#include "MRAS_System.h"
#include "NativeTextLogger.h"
#include "FakeAccelerometer.h"
#include "NativeDataLogger.h"
#include "FakeBarometer.h"
#include "StateEstimator.h"


int main() {
    TextLogger* logger = new NativeTextLogger(0);
    MRAS_System* mras = MRAS_System::get_instance();

    auto *accelerometer = new FakeAccelerometer(1);
    auto *data_logger = new NativeDataLogger(2);
    auto *barometer = new FakeBarometer(3);
    auto *altitudeEstimator = new StateEstimator(4);

    mras->set_logger(logger);

    mras->add_subsystem(accelerometer);
    mras->add_subsystem(barometer);
    mras->add_subsystem(altitudeEstimator);
    accelerometer->add_subscriber(data_logger);
    accelerometer->add_subscriber(altitudeEstimator);
    barometer->add_subscriber(data_logger);
    barometer->add_subscriber(altitudeEstimator);
    altitudeEstimator->add_subscriber(data_logger);


    mras->setup();

    mras->loop();

    return 0;
}