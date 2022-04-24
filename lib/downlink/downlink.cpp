//
// Created by Tom Danvers on 23/04/2022.
// 2022 TeamSunride.
//

#include "downlink.h"

namespace downlink {
    // Create radio driver object
    SX1262 radio = new Module(CHIP_SELECT_PIN, DIO1_PIN, RESET_PIN,
                              BUSY_PIN);

// Store radio state globally
    int radioState = 0;

// flag to indicate that a packet was sent
    volatile bool radioAvailable = true;

// disable interrupt when it's not needed
    volatile bool enableInterrupt = true;
}


int downlink::setupRadio() {
    radioState = radio.begin(frequency, bandwidth, spreadingFactor, codeRate, syncWord, power,
                             8, 0, true);
    radio.setRfSwitchPins(RX_ENABLE_PIN, TX_ENABLE_PIN);

    // set the function that will be called
    // when packet transmission is finished
    radio.setDio1Action(setFlag);

    return radioState;
}

void downlink::setFlag() {
    {
        // check if the interrupt is enabled
        if (!enableInterrupt) {
            return;
        }

        // we sent a packet, set the flag
        radioAvailable = true;

        // disable the interrupt
        enableInterrupt = false;
    }
}

int downlink::transmit(uint8_t *data, size_t len) {
    if (!radioAvailable) {
        // return 1 if the radio is busy
        return 1;
    }
    radioAvailable = false;

    radioState = radio.startTransmit(data, len);
    enableInterrupt = true;
    return radioState;
}
