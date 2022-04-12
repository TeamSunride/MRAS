//
// Created by Tom Danvers on 12/04/2022.
// 2022 TeamSunride.
//

#include "LaunchDetector.h"
#include "unity.h"


LaunchDetector launchDetector(1, 500);
float z_acceleration;

void test_with_step_input() {
    launchDetector.reset();
    bool launch_detected = false;
    int iteration_detected = 0;

    for (int i = 0; i <= 10; i++) {
        if (i <= 2) {
            z_acceleration = 0;
        } else {
            z_acceleration = 2;
        }

        if (launchDetector.run(z_acceleration) && !launch_detected) {
            iteration_detected = i;
            launch_detected = true;
        };

        delay(100);
    }

    TEST_ASSERT_EQUAL(9, iteration_detected);
}

void test_large_intervals() {
    launchDetector.reset();
    launchDetector.run(0);
    delay(100);
    launchDetector.run(2);
    delay(400);
    // at this point we have not yet been above the threshold for long enough
    TEST_ASSERT_FALSE(launchDetector.run(2))
    delay(150);
    // now we have
    TEST_ASSERT_TRUE(launchDetector.run(2))

    // if we now pass a value that is below the threshold we expect it to return false
    TEST_ASSERT_FALSE(launchDetector.run(0))
}


void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_with_step_input);
    RUN_TEST(test_large_intervals);

    UNITY_END();
}

void loop() {}