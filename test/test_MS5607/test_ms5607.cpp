//
// Created by Tom Danvers on 23/06/2022.
// 2022 TeamSunride.
//

#define MS5607_GODMODE

#include "Barometer_MS5607.h"
#include "unity.h"



Barometer_MS5607 ms5607 = Barometer_MS5607(0x76, &Wire2);

void test_MS5607_reset() {
    TEST_ASSERT_TRUE(ms5607.reset());
}

void test_ms5607_begin() {
    TEST_ASSERT_EQUAL(0, ms5607.begin());
}

void test_ms5607_read() {
    TEST_ASSERT_EQUAL(Barometer_MS5607::IDLE, ms5607.state);
    TEST_ASSERT_EQUAL(0, ms5607.readData());
    TEST_ASSERT_EQUAL(Barometer_MS5607::READING_PRESSURE, ms5607.state);
    delay(2000);
    TEST_ASSERT_EQUAL(0, ms5607.readData());
    TEST_ASSERT_EQUAL(Barometer_MS5607::READING_TEMPERATURE, ms5607.state);
    delay(2000);
    TEST_ASSERT_EQUAL(0, ms5607.readData());

    Serial.println("Pressure: " + String(ms5607.getPressure()));
    Serial.println("Temperature: " + String(ms5607.getTemperature()));
}

void setup() {
    UNITY_BEGIN();

    Wire2.begin();

    Serial.println("Testing MS5607");

    RUN_TEST(test_MS5607_reset);
    RUN_TEST(test_ms5607_begin);
    RUN_TEST(test_ms5607_read);

    UNITY_END();
}

void loop() {
}