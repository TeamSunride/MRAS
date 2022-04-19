#include <timestamp.h>
#include <unity.h>
#include "Int64String.h"
#include "TimeLib.h"

void test_timestamp() {
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

void test_rtc_sync() {
    Serial.println("Compile time timestamp: " + String(__TIMESTAMP__));

    char weekday[3];
    char month[3];
    int _day, _hour, _minute, _second, _year;

    // extract values from compile time timestamp
    sscanf(__TIMESTAMP__, "%s %s %d %d:%d:%d %d", weekday, month, &_day, &_hour, &_minute, &_second, &_year);

    // get timestamp from RTC
    time_t currentTime = now();

    Serial.println("If the following test fails, try again as the day/hour/year might have changed since compilation");

    // compare compile time and RTC time
    TEST_ASSERT_EQUAL(_day, day(currentTime));
    TEST_ASSERT_EQUAL(_hour, hour(currentTime));
    TEST_ASSERT_EQUAL(_year, year(currentTime));
}


void setup() {
    UNITY_BEGIN();

    uint32_t start = micros();
    getTimestampMillis();
    uint32_t end = micros();
    Serial.println("Timestamp generated in (microseconds): " + String(end - start));

    // run this test first as it needs to run as close to compile time as possible
    RUN_TEST(test_rtc_sync);

    RUN_TEST(test_timestamp);
    RUN_TEST(test_range);

    UNITY_END();
}

void loop() {

}