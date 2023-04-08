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
#include "cmath"

#define THRESHOLD_VELOCITY 15 //ms^-1
#define ACCELERATION_THRESHOLD 15 //ms^-2
#define ESTIMATED_PEAK_ACCELERATION 70 //ms^-2

enum phase_t {
    SETUP,      // 0
    PRELAUNCH,  // 1
    ASCENT,     // 2
    DESCENT,    // 3
    LANDED      // 4
};
enum event_t {
    NONE,       // 0
    LAUNCH,     // 1
    BURNOUT,    // 2
    APOGEE,     // 3
    TOUCHDOWN   // 4
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

    bool startBurnoutDetector = false;
    uint8_t burnoutCounter = 0;

    uint32_t setupTime = 0;
    uint16_t counter = 0;
    AccelerometerDataMsg *accelerometerDataMsg;
    float yAcceleration;

    uint32_t settleTimer = 0;
    bool settleTimerOn = false;
};


#endif //MRAS_EVENTDETECTOR_H
