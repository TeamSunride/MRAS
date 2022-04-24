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

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_radio_setup);

    UNITY_END();
}

void loop() {

}
