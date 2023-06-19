//
// Created by Tom Danvers on 06/02/2023.
//

#ifndef MRAS_ROCKETTELEMETRYSYSTEM_H
#define MRAS_ROCKETTELEMETRYSYSTEM_H


#include "TelemetrySystem.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "telemetry_messages/KAlphaTelemetryMsg.h"
#include "system_messages/GNSSDataMsg.h"

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
    KAlphaTelemetryMsg kalpha_msg;

    TelemetryDataMsg telemetry_msg;

    // array of received GNSS messages
    GNSSDataMsg gnss_data[2] = {GNSSDataMsg(), GNSSDataMsg()};
    void handle_gnss_data_msg(GNSSDataMsg *msg);
    static void copy_gnss_data(GNSSDataMsg *msg, KAlphaTelemetryMsg *dest);
};


#endif //MRAS_ROCKETTELEMETRYSYSTEM_H
