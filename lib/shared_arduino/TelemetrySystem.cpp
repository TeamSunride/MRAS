//
// Created by Tom Danvers on 05/01/2023.
//

#include "TelemetrySystem.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "system_messages/TelemetryMessageReceivedMsg.h"
#include "serializers.h"

int8_t TelemetrySystem::setup() {
    log("Starting SPI bus for radio");
    RADIO_SPI_BUS.begin();

    log("Radio startup");

    int8_t radio_power = RADIO_POWER;
    if (USING_AMPLIFIER) {
        radio_power = min((int8_t) 15, radio_power);
    }

    radio_state = radio.begin(RADIO_FREQUENCY,
                              RADIO_BANDWIDTH,
                              RADIO_SPREADING_FACTOR,
                              RADIO_CODING_RATE,
                              RADIO_SYNC_WORD,
                              radio_power,
                              RADIO_PREAMBLE_LENGTH,
                              RADIO_TCXO_VOLTAGE,
                              RADIO_USE_LDO);

    if (radio_state != RADIOLIB_ERR_NONE) {
        log("Radio begin() failed. RadioLib error code: %d", radio_state);
        return -1;
    } else {
        log("Radio begin() successful");
    }

    log("Setting RF switch pins");
    radio.setRfSwitchPins(RADIO_RX_ENABLE_PIN, RADIO_TX_ENABLE_PIN);

    // Not using explicit header mode on KAlpha to optimise packet size
//    log("Setting explicit header mode");
//    radio_state = radio.explicitHeader();
//    if (radio_state == RADIOLIB_ERR_NONE) {
//        log("Successfully set explicit header mode");
//    }

    log("Setting CRC configuration");
    radio_state = radio.setCRC(1);
    if (radio_state == RADIOLIB_ERR_NONE) {
        log("Successfully enabled CRC checking");
    }


    if (radio_state != RADIOLIB_ERR_NONE) {
        log("Failed to enter explicit header mode. RadioLib error code: %d", radio_state);
        return -1;
    } else {
        log("Radio entered explicit header mode");
    }

    log("Radio setup complete");

    return 0;
}

//TelemetryMessageQueueMsg *TelemetrySystem::get_default_message() {
//    auto *message = new TelemetryDataMsg();
//    message->x = 1;
//    message->y = 2;
//    message->z = 3;
//
//    auto *queue_message = new TelemetryMessageQueueMsg();
//    queue_message->telemetry_message = message;
//    queue_message->size = sizeof(TelemetryDataMsg);
//
//    return queue_message;
//}

void TelemetrySystem::transmit_next_message() {
    if (!TRANSMIT_TELEMETRY) {
        return;
    }

    TelemetryMessageQueueMsg *next_message = get_default_message();
    // log("Transmitting new telemetry message size %d", next_message->size);
    auto* bytes_to_transmit = (uint8_t *) next_message->telemetry_message;
    radio.startTransmit(bytes_to_transmit, next_message->size);
    telemetry_system_state = TX;

    delete next_message;
}

void TelemetrySystem::start_receiving_next_message(uint32_t timeout) {
    // log("Receiving new telemetry message");
    radio.startReceive(timeout);
    telemetry_system_state = RX;
}

bool TelemetrySystem::read_new_message_from_buffer(TelemetryMessageReceivedMsg* output, bool receive_again) {
    radio_state = radio.readData((uint8_t*) output->telemetry_message, 0);

    if (receive_again) start_receiving_next_message();

    if (radio_state == RADIOLIB_ERR_CRC_MISMATCH) {
        // The calculated and expected CRCs of received packet do not match.
        // log("CRC error");
        return false;
    }

    if (radio_state == RADIOLIB_ERR_NONE) {
        return true;
    } else {
        log("RadioLib error code: %d", radio_state);
        return false;
    }
}

int16_t TelemetrySystem::get_radio_state() const {
    return radio_state;
}
