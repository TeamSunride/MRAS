//
// Created by Tom Danvers on 24/04/2022.
// 2022 TeamSunride.
//

#include "unity.h"
#include "downlink.h"


uint8_t message[3] = {1, 2, 3};
uint8_t receivedMessage[3] = {0, 0, 0};


unsigned int iterations = 0;

void test_radio_setup() {
    TEST_ASSERT_EQUAL_MESSAGE(0, downlink::setupRadio(), "Radio failed to start - view here for status codes "
                                                         "https://jgromes.github.io/RadioLib/group__status__codes.html");
}

void check_received_data() {
    TEST_ASSERT_EQUAL(message[0], receivedMessage[0]);
    TEST_ASSERT_EQUAL(message[1], receivedMessage[1]);
    TEST_ASSERT_EQUAL(message[2], receivedMessage[2]);
}

uint32_t ground_timeout_start = 0;
#define GROUND_TIMEOUT_MILLISECONDS 1000

void setup() {
    // Wait for Serial connection before starting test
    Serial.begin(115200);
    while (!Serial) {}

    UNITY_BEGIN();

    RUN_TEST(test_radio_setup);

#ifdef TEST_RADIO_ROCKET
    UNITY_END();
#endif

    ground_timeout_start = millis();
}

// I understand that the code that follows is barely readable
void loop() {
#ifdef TEST_RADIO_GROUND
    // if the ground station reception of the pong timed out, assert that the radio is available
    if (millis() - ground_timeout_start > GROUND_TIMEOUT_MILLISECONDS && downlink::lastAction == downlink::RECEIVE) {
        downlink::radioAvailable = true;
        Serial.println("Timed out waiting for response");
        downlink::lastAction = downlink::NONE;
    }
#endif

    if (!downlink::radioAvailable) return;

    switch (downlink::lastAction) {
        case downlink::NONE:
            Serial.println("Starting up with transmission");
            if (RADIOLIB_ERR_NONE != downlink::transmit(message, sizeof message)) {
                Serial.println("Transmission failed. Error code: " + String(downlink::radioState));
                delay(500);
            }
            break;
        case downlink::TRANSMIT:
            // we just transmitted a message, wait for the response
#ifdef TEST_RADIO_ROCKET
            downlink::receive(); // infinite timeout, wait for next transmission from ground
#elif TEST_RADIO_GROUND
            Serial.println("Waiting for response from rocket");
            downlink::receive();
            ground_timeout_start = millis();
#endif
            break;
        case downlink::RECEIVE:
            // we just received a message, read out the response and then transmit another

            // clear the buffer to store the received data in
            memset(receivedMessage, 0, 3);

            // read received data from the radio into the buffer
            downlink::radioState = downlink::radio.readData(receivedMessage, sizeof receivedMessage);
            Serial.println("Received a message! Radio state: " + String(downlink::radioState));

#ifdef TEST_RADIO_ROCKET
            // if we are the "transmitter" (THE ROCKET IN THIS CASE) then echo the message back
            // to the ground station only if it was received properly with no errors
            if (downlink::radioState == RADIOLIB_ERR_NONE)
                downlink::transmit(receivedMessage, sizeof receivedMessage);


#elif TEST_RADIO_GROUND

            Serial.print("Message contents: ");
            Serial.println(String(receivedMessage[0]) + " " + String(receivedMessage[1])  + " " + String(receivedMessage[2]));

            iterations++;

            RUN_TEST(check_received_data);

            delay(1000);

            Serial.println("=================================");
            Serial.println("Transmitting new message");
            // the "receiver" (THE GROUND STATION) sends a new message to the rocket
            downlink::transmit(message, sizeof message);
#endif
            break;
    }

    if (iterations >= 10) {
        UNITY_END();
    }
}
