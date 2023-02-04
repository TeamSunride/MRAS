//
// Created by Tom Danvers on 05/01/2023.
//

#ifndef MRAS_TELEMETRYSYSTEM_H
#define MRAS_TELEMETRYSYSTEM_H


#include "Subsystem.h"
#include "RadioLib.h"
#include "MRAS_Config.h"
#include "TelemetryMessage.h"
#include "system_messages/QueueTelemetryMessageMsg.h"

class TelemetrySystem : public Subsystem {
private:
    // create subsystem boilerplate
    SUBSYSTEM_NAME("TelemetrySystem")
    SUBSYSTEM_NO_MESSAGE_HANDLER

    // create setup and loop functions
    int8_t setup() override;

    int8_t loop() override;

    SX1262 radio = new Module(RADIO_CHIP_SELECT_PIN,
                              RADIO_DIO1_PIN,
                              RADIO_RESET_PIN,
                              RADIO_BUSY_PIN,
                              RADIO_SPI_BUS);

    enum RadioState {
        RADIO_STATE_IDLE,
        RADIO_STATE_TX,
        RADIO_STATE_RX
    } radio_state = RADIO_STATE_IDLE;

    uint8_t radio_buffer[255];

    bool radio_available();

    QueueTelemetryMessageMsg* get_next_message();

    void transmit_next_message();
    void receive_next_message(uint32_t timeout = 0xFFFFFF);

public:
    enum TelemetrySystemType {
        GROUND,
        ROCKET
    } telemetry_system_type;

    explicit TelemetrySystem(uint8_t id, TelemetrySystemType type) : Subsystem(id) {
        telemetry_system_type = type;
    }
};


#endif //MRAS_TELEMETRYSYSTEM_H
