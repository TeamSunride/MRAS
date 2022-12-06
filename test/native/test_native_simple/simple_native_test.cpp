//
// Created by Tom Danvers on 05/12/2022.
//

#include "unity.h"

void setUp() {
    // set stuff up here
}

void tearDown() {
    // clean stuff up here
}

void simple_test() {
    TEST_ASSERT_EQUAL(4, 3+1);
}

int main() {

    UNITY_BEGIN();

    RUN_TEST(simple_test);

    UNITY_END();

    return 0;
}