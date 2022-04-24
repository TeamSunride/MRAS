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

void test_downlink_transmit() {
    uint8_t buffer[32];

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

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_radio_setup);
    RUN_TEST(test_downlink_transmit);

    UNITY_END();
}

void loop() {

}
