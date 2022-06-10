//
// Created by Tom Danvers on 23/04/2022.
// 2022 TeamSunride.
//

#include "downlink.h"
#include "Arduino.h"

namespace downlink {
    // Create radio driver object

#ifdef DART_PINS
    SX1262 radio = new Module(CHIP_SELECT_PIN, DIO1_PIN, RESET_PIN,
                              BUSY_PIN, SPI1);
#else
    SX1262 radio = new Module(CHIP_SELECT_PIN, DIO1_PIN, RESET_PIN,
                              BUSY_PIN);
#endif

// Store radio state globally
    int radioState = 0;

// flag to indicate that a packet was sent
    volatile bool radioAvailable = true;

// disable interrupt when it's not needed
    volatile bool enableInterrupt = true;

    DownlinkActionType volatile lastAction = NONE;
}


int downlink::setupRadio(bool explicitHeader) {
#ifdef DART_PINS
    SPI1.begin();  // DART uses SPI1 for SX1262
#endif

    Serial.println("Calling radio.begin(): ");
    radioState = radio.begin(frequency, bandwidth, spreadingFactor, codeRate, syncWord, power,
                             8, 0, true);
    Serial.println("Setting RF switch pins: ");
    radio.setRfSwitchPins(RX_ENABLE_PIN, TX_ENABLE_PIN);
    Serial.println("Setting DIO1 action: ");
    // set the function that will be called
    // when packet transmission is finished
    radio.setDio1Action(setFlag);

    if (explicitHeader) {
        radioState = radio.explicitHeader();
    }

    Serial.println("Radio state: " + String(radioState));
    return radioState;
}

void downlink::setFlag() {
    // check if the interrupt is enabled
    if (!enableInterrupt) {
        return;
    }

    // we sent a packet, set the flag
    radioAvailable = true;

    // disable the interrupt
    enableInterrupt = false;
}

int downlink::transmit(uint8_t *data, size_t len) {
    if (!radioAvailable) {
        // return 1 if the radio is busy
        return 1;
    }

    radioState = radio.startTransmit(data, len);
    if (radioState == RADIOLIB_ERR_NONE) {
        radioAvailable = false;
        lastAction = TRANSMIT;
        enableInterrupt = true;
    }
    return radioState;
}

int downlink::receive(uint32_t timeout) {
    if (!radioAvailable) {
        // return 1 if the radio is busy
        return 1;
    }

    radioState = radio.startReceive(timeout);
    if (radioState == RADIOLIB_ERR_NONE) {
        radioAvailable = false;
        lastAction = RECEIVE;
        enableInterrupt = true;
    }
    return radioState;
}
