//
// Created by Tom Danvers on 10/07/2022.
// 2022 TeamSunride.
//

#include "unity.h"
#include "Arduino.h"
#include "Accelerometer_ADXL375.h"
#include "Int64String.h" // pio being really weird again

Accelerometer_ADXL375 adxl = Accelerometer_ADXL375(&Wire2, 0x53);

void test_adxl375_begin() {
    TEST_ASSERT_EQUAL(0, adxl.begin());
}

void test_adxl375_readData() {
    /*
    for (int i=0; i < 5000;i++) {
        adxl.readData();
        delay(10);
    }
    */
    TEST_ASSERT_EQUAL(0, adxl.readData());
}

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_adxl375_begin);

    delay(500);

    RUN_TEST(test_adxl375_readData);

    UNITY_END();
}

void loop() {}