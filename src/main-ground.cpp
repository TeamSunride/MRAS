//
// Created by Tom Danvers on 24/04/2022.
// 2022 TeamSunride.
// This file runs if built with the "ground" environment
//

#include <Arduino.h>
#include "downlink.h"
#include "payloads/Test_Payload.h"

uint8_t radioBuffer[255];

void setup() {
    Serial.begin(115200);
    while (!Serial) {}
    downlink::setupRadio();
    Serial.println("Finished setting up radio. State: " + String(downlink::radioState));

    // start receiving data
    downlink::receive();
    Serial.println("Started receiving");
}
void loop() {
    if (downlink::radioAvailable) {

        // clear the radio buffer
        memset(radioBuffer, 0, sizeof radioBuffer);

        // output all data into the buffer. Setting `len` to zero retrieves the packet length automatically
        downlink::radio.readData(radioBuffer, 0);

        // determine which payload type was received by reading the first byte
        auto receivedPayloadType = static_cast<downlink::PayloadType>(radioBuffer[0]);

        switch (receivedPayloadType) {
            case downlink::UNDEFINED:
                Serial.println("Received undefined payload type, cannot print result");
                break;
            case downlink::Test_Payload_Type:
                Test_Payload testPayload = fromByteArray<Test_Payload>(radioBuffer);
                Serial.println("Received payload: " + testPayload.toLineProtocol());
                break;
        }

        // put the radio back into receive mode
        downlink::receive();
    }
}