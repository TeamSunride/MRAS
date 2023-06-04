//
// Created by Tom Danvers on 06/02/2023.
//

#ifndef MRAS_ROCKETTELEMETRYSYSTEM_H
#define MRAS_ROCKETTELEMETRYSYSTEM_H


#include "TelemetrySystem.h"
#include "telemetry_messages/TelemetryDataMsg.h"

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

    TelemetryMessageQueueMsg* get_default_message() override;

    void on_message(SystemMessage *msg) override;
private:
    float latitude1 = 0;
    float longitude1 = 0;
    uint16_t altitude1 = 0;
    uint8_t fix_type1 = 0;
    uint8_t satellites1 = 0;
    float latitude2 = 0;
    float longitude2 = 0;
    uint16_t altitude2 = 0;
    uint8_t fix_type2 = 0;
    uint8_t satellites2 = 0;
    float x_acceleration = 0;
    float pressure = 0;
    float temperature = 0;
    float altitude_estimate = 0;

    TelemetryDataMsg telemetry_msg;
};


#endif //MRAS_ROCKETTELEMETRYSYSTEM_H
