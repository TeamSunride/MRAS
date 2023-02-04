//
// Created by Tom Danvers on 05/01/2023.
//

#include "TelemetrySystem.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "system_messages/ReceivedTelemetryMessageMsg.h"
#include "serializers.h"

int8_t TelemetrySystem::setup() {
    log("Starting SPI bus for radio");
    RADIO_SPI_BUS.begin();

    log("Radio startup");

    int radio_state = 0;

    radio_state = radio.begin(RADIO_FREQUENCY,
                              RADIO_BANDWIDTH,
                              RADIO_SPREADING_FACTOR,
                              RADIO_CODING_RATE,
                              RADIO_SYNC_WORD,
                              RADIO_POWER,
                              RADIO_PREAMBLE_LENGTH,
                              RADIO_TCXO_VOLTAGE,
                              RADIO_USE_LDO);

    if (radio_state != RADIOLIB_ERR_NONE) {
        log("Radio begin() failed. RadioLib error code: %d", radio_state);
        return -1;
    } else {
        log("Radio begin() successful");
    }

    radio.setRfSwitchPins(RADIO_RX_ENABLE_PIN, RADIO_TX_ENABLE_PIN);

    radio_state = radio.explicitHeader();

    if (radio_state != RADIOLIB_ERR_NONE) {
        log("Failed to enter explicit header mode. RadioLib error code: %d", radio_state);
        return -1;
    } else {
        log("Radio entered explicit header mode");
    }

    log("Radio setup complete");

    return 0;
}

int8_t TelemetrySystem::loop() {

    Module *mod = radio.getMod();
    if (radio_state != RADIO_STATE_IDLE) {
        // check interrupt pin of radio and return if the radio is busy
        if (!mod->digitalRead(mod->getIrq())) {
            return 0;
        }

        radio.finishTransmit();
    }

    switch (radio_state) {
        case RADIO_STATE_IDLE: {
            // if we are the ground station, start receiving
            if (telemetry_system_type == GROUND) {
                receive_next_message();
            } else if (telemetry_system_type == ROCKET) {
                transmit_next_message();
            }
            break;
        }
        case RADIO_STATE_TX: {
            transmit_next_message();
            break;
        }
        case RADIO_STATE_RX: {
            uint8_t radioBuffer[255];

            int state = radio.readData(radioBuffer, 0);

            receive_next_message();

            // TODO: CRC CHECK

            // process the new message
            auto telemetry_message = (TelemetryMessage*) radioBuffer;

            auto *received_message = new ReceivedTelemetryMessageMsg();
            received_message->telemetry_message = telemetry_message;
            publish(received_message);
        }
    }
    return 0;
}

bool TelemetrySystem::radio_available() {
    // radio is available for next transmit when the IRQ pin is high
    return radio.getMod()->digitalRead(radio.getMod()->getIrq());
}

QueueTelemetryMessageMsg *TelemetrySystem::get_next_message() {
    auto *message = new TelemetryDataMsg();
    message->x = 1;
    message->y = 2;
    message->z = 3;

    auto *queue_message = new QueueTelemetryMessageMsg();
    queue_message->telemetry_message = message;
    queue_message->size = sizeof(TelemetryDataMsg);

    return queue_message;
}

void TelemetrySystem::transmit_next_message() {

    QueueTelemetryMessageMsg *next_message = get_next_message();
    log("Transmitting new telemetry message size %d", next_message->size);
    auto* bytes_to_transmit = (uint8_t *) next_message->telemetry_message;
    radio.startTransmit(bytes_to_transmit, next_message->size);
    radio_state = RADIO_STATE_TX;

    delete next_message->telemetry_message;
}

void TelemetrySystem::receive_next_message(uint32_t timeout) {
    log("Receiving new telemetry message");
    radio.startReceive(timeout);
    radio_state = RADIO_STATE_RX;
}
