//
// Created by Tom Danvers on 23/04/2022.
// 2022 TeamSunride.
//

#ifndef DOWNLINK_H
#define DOWNLINK_H

#include "RadioLib.h"
#include "serializers.h"
#include "payload_types.h"

namespace downlink {

    // ===[ RADIO SETTINGS ]===

    const float frequency = 868.0;  // Carrier frequency in MHz
    const float bandwidth = 500.0;  // LoRa bandwidth in kHz
    const uint8_t spreadingFactor = 5;  // LoRa spreading factor
    const uint8_t codeRate = 5; // LoRa coding rate denominator.
    const uint8_t syncWord = 0x22;  // 2-byte LoRa sync word
    const int8_t power = 14 // output power in dBm

    // ===[ RADIO PIN DEFINITIONS ]===

    #ifdef TEENSY_RADIO_BREADBOARD_PINS

    #define CHIP_SELECT_PIN     10
    #define DIO1_PIN            5
    #define RESET_PIN           6
    #define BUSY_PIN            4
    #define RX_ENABLE_PIN       2
    #define TX_ENABLE_PIN       3

    #elif DART_PINS

    #define CHIP_SELECT_PIN     0
    #define DIO1_PIN            31
    #define RESET_PIN           32
    #define BUSY_PIN            33
    #define RX_ENABLE_PIN       34
    #define TX_ENABLE_PIN       35

    #elif NRF52840_FEATHER_SENSE_RADIO_BREADBOARD_PINS

    #define CHIP_SELECT_PIN     2
    #define DIO1_PIN            5
    #define RESET_PIN           11
    #define BUSY_PIN            6
    #define RX_ENABLE_PIN       10
    #define TX_ENABLE_PIN       9

#elif GS_V1_PINS

    #define CHIP_SELECT_PIN     0
    #define DIO1_PIN            1
    #define RESET_PIN           10
    #define BUSY_PIN            9
    #define RX_ENABLE_PIN       6
    #define TX_ENABLE_PIN       5

#elif MRAS_DART_PINS

//    #define CHIP_SELECT_PIN     31
//    #define DIO1_PIN            33
//    #define RESET_PIN           32
//    #define BUSY_PIN            34
//    #define RX_ENABLE_PIN       36
//    #define TX_ENABLE_PIN       35

// TEMPORARY CHANGE FOR TESTING
    #define CHIP_SELECT_PIN     10
    #define DIO1_PIN            5
    #define RESET_PIN           6
    #define BUSY_PIN            4
    #define RX_ENABLE_PIN       2
    #define TX_ENABLE_PIN       3

    # else

    // Default pin values for radio (with ARDUINO):
    #define CHIP_SELECT_PIN     10
    #define DIO1_PIN            2
    #define RESET_PIN           9
    #define BUSY_PIN            5
    #define RX_ENABLE_PIN       7
    #define TX_ENABLE_PIN       6

    #endif

    /**
     * Initialise the radio with the parameters corresponding to the selected build environment
     * Refer to `downlink.h` to set these parameters
     * @return RadioLib status code
     */
    int setupRadio(bool explicitHeader = true);

    // this function is called when a complete packet
    // is transmitted by the module
    void setFlag();

    /**
     * Transmit data via the radio in a non-blocking manner. Returns 1 if the radio is currently busy
     * @param data Binary data to be transmitted
     * @param len The length of binary data to be transmitted
     * @return RadioLib status code, or 1 if the radio is busy
     */
    int transmit(uint8_t* data, size_t len);

    /**
     *
     * @return RadioLib status code, or 1 if the radio is busy
     */
    int receive(uint32_t timeout = 0xFFFFFF);

    // https://community.platformio.org/t/platformio-doesnt-compile-when-header-contains-global-variables/6687

    // Create radio driver object
    extern SX1262 radio;

    // Store radio state globally
    extern int radioState;

    // flag to indicate that a packet was sent
    extern volatile bool radioAvailable;

    extern volatile enum DownlinkActionType{
        NONE,
        TRANSMIT,
        RECEIVE
    } lastAction;

    // disable interrupt when it's not needed
    extern volatile bool enableInterrupt;
}


#endif //DOWNLINK_H
