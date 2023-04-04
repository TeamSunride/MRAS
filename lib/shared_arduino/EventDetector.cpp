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
        case SETUP:{
            if (millis() - setupTime > 10000) {
                phase = PRELAUNCH;
            }
            break;
        }
        case PRELAUNCH:{
            if (velocity > THRESHOLD_VELOCITY) {
                phase = ASCENT;
                event = LAUNCH;
            }
            break;
        }
        case ASCENT:{
            if (velocity < 0){
                phase = DESCENT;
                event = APOGEE;
                apogee = altitude;
                prevAltitude = altitude;
            }
            if (yAcceleration > ACCELERATION_THRESHOLD){
                event = BURNOUT;
                burnoutCounter++;
            }
            break;
        }
        case DESCENT:{
            if (prevAltitude - altitude < 4){
                counter++;
                prevAltitude = altitude;
            }
            else{
                counter = 0;
                prevAltitude = altitude;
            }
            if (counter > 10000){       // 10 seconds if dt is 0.001
                phase = LANDED;
                event = TOUCHDOWN;
            }
            break;
        }
        case LANDED:
            break;
    }
    auto eventMsg = new EventDetectorMsg();
    eventMsg->event = event;
    eventMsg->phase = phase;
    publish(eventMsg);
    return 0;
}

void EventDetector::on_message(SystemMessage *msg) {
    if (msg->get_type() == StateEstimatorMsg_t) {
        stateEstimatorMsg = (StateEstimatorMsg *) msg;
        altitude = stateEstimatorMsg->estimatedAltitude;
        velocity = stateEstimatorMsg->estimatedVelocity;
    }
    if (msg->get_type() == AccelerometerDataMsg_t){
        accelerometerDataMsg = (AccelerometerDataMsg *) msg;
        yAcceleration = accelerometerDataMsg->acceleration[1];
    }
}
