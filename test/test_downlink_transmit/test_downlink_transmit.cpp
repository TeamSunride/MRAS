//
// Created by Tom Danvers on 24/04/2022.
// 2022 TeamSunride.
//

#include "unity.h"
#include "downlink.h"

void test_radio_setup() {
    TEST_ASSERT_EQUAL_MESSAGE(0, downlink::setupRadio(), "Radio failed to start - view here for status codes "
                                                         "https://jgromes.github.io/RadioLib/group__status__codes.html");
}

uint8_t buffer[3] = {1, 2, 3};

void test_downlink_transmit() {

    // we expect the first transmission to work without any error (an error is when the return value =/= 0)
    TEST_ASSERT_EQUAL(0, downlink::transmit(buffer, sizeof buffer));

    // if we attempt transmission again straight away then the function will return 1 as the radio is busy
    TEST_ASSERT_EQUAL(1, downlink::transmit(buffer, sizeof buffer));

    // but if we delay 1 second, the radio should be ready again, so transmission should work as expected
    delay(1000);
    TEST_ASSERT_EQUAL(0, downlink::transmit(buffer, sizeof buffer));

    // check to see if the radio is working with no errors
    TEST_ASSERT_EQUAL(0, downlink::radioState);
}

void test_receiver() {
    delay(1000);
    TEST_ASSERT_EQUAL(RADIOLIB_ERR_NONE, downlink::receive());
    // wait for radio to finish receiving
    delay(1000);

    TEST_ASSERT_TRUE(downlink::radioAvailable);

    TEST_ASSERT_EQUAL(downlink::lastAction, downlink::RECEIVE);
    uint8_t receivedData[sizeof buffer] = {0, 0, 0};
    downlink::radio.readData(receivedData, sizeof receivedData);
    Serial.println("Received data: ");
    Serial.println(receivedData[0]);
    Serial.println(receivedData[1]);
    Serial.println(receivedData[2]);
    TEST_ASSERT_EQUAL(buffer[0], receivedData[0]);
    TEST_ASSERT_EQUAL(buffer[1], receivedData[1]);
    TEST_ASSERT_EQUAL(buffer[2], receivedData[2]);

}

void setup() {
    // Wait for Serial connection before starting test
    Serial.begin(115200);
    while (!Serial) {}

    UNITY_BEGIN();


    RUN_TEST(test_radio_setup);
    RUN_TEST(test_downlink_transmit);

    Serial.println("CHIP_SELECT_PIN: " + String(CHIP_SELECT_PIN));
    Serial.println("DIO1_PIN: " + String(DIO1_PIN));
    Serial.println("RESET_PIN: " + String(RESET_PIN));
    Serial.println("BUSY_PIN: " + String(BUSY_PIN));
    Serial.println("RX_ENABLE_PIN: " + String(RX_ENABLE_PIN));
    Serial.println("TX_ENABLE_PIN: " + String(TX_ENABLE_PIN));

    // if this is the transmitter, end the test here and move on to the main loop
#if TEST_RADIO_ROCKET
    UNITY_END();
#elif TEST_RADIO_GROUND
    RUN_TEST(test_receiver);
#endif

    UNITY_END();
}

void loop() {
#if TEST_RADIO_ROCKET // this is the transmitter environment
    if (downlink::radioAvailable) {
        downlink::transmit(buffer, sizeof buffer);
    }
#endif
}
