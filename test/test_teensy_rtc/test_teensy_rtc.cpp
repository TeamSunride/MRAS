#include <timestamp.h>
#include <unity.h>
#include "Int64String.h"
#include "TimeLib.h"

void test_units_milliseconds() {
    uint64_t t1 = getTimestampMillis();
    delay(1000);
    uint64_t t2 = getTimestampMillis();

    Serial.println("t1: " + int64String(t1));
    Serial.println("t2: " + int64String(t2));

    // we expect dT to equal 1000ms
    uint64_t dT = t2 - t1;
    TEST_ASSERT_TRUE(dT <= 1001 && dT >= 999); // allow for a small amount of error
}

void test_range() {
    uint64_t t1 = getTimestampMillis();
    uint64_t THRESHOLD = 1650393336773ULL; // Tue Apr 19 2022 18:35:36 GMT+0000

    // we expect the result to be a time after Tue Apr 19 2022 18:35:36 GMT+0000
    TEST_ASSERT_TRUE_MESSAGE(t1 > THRESHOLD, "The RTC did not sync properly. Make sure you are using "
                                             "teensy-gui and not teensy-cli as the upload_protocol in platformio.ini. "
                                             "The time reported by the RTC was before Tue Apr 19 2022 18:35:36 GMT+0000");
}

void test_unix_timestamp() {
    // as a platformIO build option we can pass in a UNIX timestamp (see platformio.ini)
    // https://docs.platformio.org/en/stable/projectconf/section_env_build.html#built-in-variables

    // so we compare this to the time in the RTC to see if there is any sizeable offset
    Serial.println("UNIX time: " + String(UNIX_TIME));
    Serial.println("Now: " + String(now()));
    int32_t time_difference = UNIX_TIME - now();

    // make sure the time difference between now and UTC is less than 14 hours (plus 100 seconds to account for
    // acceptable compile time range)
    TEST_ASSERT_LESS_OR_EQUAL_INT32_MESSAGE(3600 * 14 + 100, abs(time_difference),
                                            "The observed time is beyond the possible UTC timezone offset of 14 hours");

    Serial.println("time_difference: " + String(time_difference));

    // timezones may be offset by 1 hour, so we do modulus division with 3600
    uint32_t offset = time_difference % 3600;

    // assert that `now` and `UNIX_TIME` should not be more than 50 seconds apart (100 covers both sides)
    TEST_ASSERT_INT32_WITHIN_MESSAGE(100, 0, offset, "The RTC did not sync properly. Make sure you are using"
                                                     "teensy-gui and not teensy-cli as the upload_protocol in platformio.ini.");

}


void setup() {
    UNITY_BEGIN();

    setSyncProvider(getTeensy3Time);

    uint32_t start = micros();
    getTimestampMillis();
    uint32_t end = micros();
    Serial.println("Timestamp generated in (microseconds): " + String(end - start));

    // run this test first as it needs to run as close to compile time as possible
    RUN_TEST(test_unix_timestamp);

    RUN_TEST(test_units_milliseconds);
    RUN_TEST(test_range);

    UNITY_END();
}

void loop() {

}