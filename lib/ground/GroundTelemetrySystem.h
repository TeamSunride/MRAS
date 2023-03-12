//
// Created by Tom Danvers on 06/02/2023.
//

#ifndef MRAS_GROUNDTELEMETRYSYSTEM_H
#define MRAS_GROUNDTELEMETRYSYSTEM_H


#include "TelemetrySystem.h"

/**
 * @brief Telemetry system for the ground station
 *
 * This class is the variant of the TelemetrySystem that is specific to the ground station
 *
 * The loop() function is set to enter receive mode first. If a message is received, it will be handled, and the
 * GroundTelemetrySystem Subsystem will emit a ReceivedTelemetryMessageMsg to all of its subscribers.
 */
class GroundTelemetrySystem : public TelemetrySystem {
    using TelemetrySystem::TelemetrySystem;
    SUBSYSTEM_NO_MESSAGE_HANDLER

    int8_t loop() override;

    TelemetryMessageQueueMsg* get_default_message() override;

    int16_t packets_received = 0;
    uint32_t last_PPS_count = 0;
    uint16_t PPS = 0;
};


#endif //MRAS_GROUNDTELEMETRYSYSTEM_H
