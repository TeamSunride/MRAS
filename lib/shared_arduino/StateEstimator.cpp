// 10/02/2023 -- Nikilesh
#include "StateEstimator.h"


int8_t StateEstimator::setup() {

    log("State Estimator initialized...");
    currentMillis = millis();
    return 0;
}

int8_t StateEstimator::loop() {
    if (start == 0) {
        return 0;
    }
    if ((currentMillis - prevMillis) < (uint32_t) (1000 * Filter->get_timeStep())) {
        return 0;
    }
    Filter->predict(yAcceleration);
    Filter->update(pressure);
    altitude = Filter->get_altitude();
    velocity = Filter->get_velocity();

/*
    switch (phase) {
        case 0:
            if (velocity > THRESHOLD_VELOCITY) {
                phase = 1; // LAUNCH
            }
        case 1:
            if (altitude < prevAltitude) {
                phase = 2; // APOGEE
            }
        case 2:
            if (velocity < THRESHOLD_VELOCITY) {
                phase = 0; // LANDING
            }
    }
*/
    auto stateMsg = new StateEstimatorMsg();

    stateMsg->estimatedAltitude = altitude;
    stateMsg->estimatedVelocity = velocity;
    //stateMsg->phase = phase;

    publish(stateMsg);


    currentMillis = millis();
    return 0;
}


float StateEstimator::altitudeEstimate(float pressure) {
    Atmosphere rocket(pressure);
    return rocket.get_altitude();
}


void StateEstimator::on_message(SystemMessage *msg) {

    if (msg->get_type() == BarometerDataMsg_t) {
        altimeter = (BarometerDataMsg *) msg;
        pressure = altimeter->pressure;
        receivedBaro = true;

    } else if (msg->get_type() == AccelerometerDataMsg_t) {
        acceleration = (AccelerometerDataMsg *) msg;
        yAcceleration = acceleration->acceleration[1];
        receivedAcc = true;

    }

    // Only runs once when it receives both messages.
    if (receivedBaro && receivedAcc && !start) {
        altitude = altitudeEstimate(pressure);
        Filter->initialize(altitude, 0.0);
        start = true;
    }

}

