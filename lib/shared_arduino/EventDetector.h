//
// Created by Nikilesh Ramesh on 03/04/2023.
//

#ifndef MRAS_EVENTDETECTOR_H
#define MRAS_EVENTDETECTOR_H


#include "Subsystem.h"
#include "system_messages/StateEstimatorMsg.h"
#include "Arduino.h"
#include "system_messages/EventDetectorMsg.h"
#include "system_messages/AccelerometerDataMsg.h"

#define THRESHOLD_VELOCITY 25 //ms^-1
#define ACCELERATION_THRESHOLD 5 //ms^-2


enum phase_t {
    SETUP,
    PRELAUNCH,
    ASCENT,
    DESCENT,
    LANDED
};
enum event_t {
    NONE,
    LAUNCH,
    BURNOUT,
    APOGEE,
    TOUCHDOWN
};

/**
 * @brief A subsystem that detects Events with the state estimator data.
 */
class EventDetector : public Subsystem {
public:
    using Subsystem::Subsystem;
    int8_t setup() override;
    int8_t loop() override;

    void on_message(SystemMessage *msg) override;

    SUBSYSTEM_NAME("EventDetector")
private:
    StateEstimatorMsg *stateEstimatorMsg{};
    float altitude = 0;
    float velocity = 0;
    float prevAltitude = 0;
    float apogee = 0;

    phase_t phase;
    event_t event;

    uint8_t burnoutCounter = 0;

    uint32_t setupTime = 0;
    uint16_t counter = 0;
    AccelerometerDataMsg *accelerometerDataMsg;
    float yAcceleration;
};


#endif //MRAS_EVENTDETECTOR_H
