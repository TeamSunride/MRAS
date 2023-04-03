//
// Created by Nikilesh Ramesh on 03/04/2023.
//

#include "EventDetector.h"

int8_t EventDetector::setup() {
    phase = SETUP;
    event = NONE;
    setupTime = millis();
    return 0;
}

int8_t EventDetector::loop() {
    switch (phase) {
        case SETUP:
            if (millis() - setupTime > 10000) {
                phase = PRELAUNCH;
            }
            break;
        case PRELAUNCH:
            if (velocity > THRESHOLD_VELOCITY) {
                phase = ASCENT;
                event = LAUNCH;
            }
            break;
        case ASCENT:
            if (velocity > 0){
                phase = DESCENT;
                event = APOGEE;
                apogee = altitude;
                prevAltitude = altitude;
            }
            break;
        case DESCENT:
            if (prevAltitude - altitude < 4){
                phase = LANDED;
                event = TOUCHDOWN;
                prevAltitude = altitude;
            }
            break;

    }
    return 0;
}

void EventDetector::on_message(SystemMessage *msg) {
    if (msg->get_type() == StateEstimatorMsg_t) {
        stateEstimatorMsg = (StateEstimatorMsg *) msg;
        altitude = stateEstimatorMsg->estimatedAltitude;
        velocity = stateEstimatorMsg->estimatedVelocity;
    }
}
