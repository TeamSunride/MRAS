//
// Created by Tom Danvers on 05/01/2023.
//

#include "TelemetrySystem.h"

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
    return 0;
}
