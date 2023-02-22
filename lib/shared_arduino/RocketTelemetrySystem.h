//
// Created by Tom Danvers on 06/02/2023.
//

#ifndef MRAS_ROCKETTELEMETRYSYSTEM_H
#define MRAS_ROCKETTELEMETRYSYSTEM_H


#include "TelemetrySystem.h"

/**
 * @brief The telemetry system for the rocket
 *
 * This class is a variant of the TelemetrySystem that is specific to the rocket
 *
 * The loop() function is set to enter transmit mode first. If a message is received, it will be handled, and the
 * RocketTelemetrySystem Subsystem will emit a ReceivedTelemetryMessageMsg to all of its subscribers.
 */
class RocketTelemetrySystem : public TelemetrySystem {
    using TelemetrySystem::TelemetrySystem;

    int8_t loop() override;
};


#endif //MRAS_ROCKETTELEMETRYSYSTEM_H
