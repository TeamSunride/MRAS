#include <timestamp.h>
#include <unity.h>
#include "Int64String.h"

void test_timestamp() {
    uint64_t t1 = getTimestampMillis();
    delay(1000);
    uint64_t t2 = getTimestampMillis();

    Serial.println("t1: " + int64String(t1));
    Serial.println("t2: " + int64String(t2));

    // we expect dT to equal 1000ms
    TEST_ASSERT_EQUAL(t2 - t1, 1000);
}

void test_range() {
    uint64_t t1 = getTimestampMillis();
    uint64_t THRESHOLD = 1650393336773ULL; // Tue Apr 19 2022 18:35:36 GMT+0000

    // we expect the result to be a time after Tue Apr 19 2022 18:35:36 GMT+0000
    TEST_ASSERT_TRUE_MESSAGE(t1 > THRESHOLD, "The RTC did not sync properly. Make sure you are using "
                                             "teensy-gui and not teensy-cli as the upload_protocol. "
                                             "The time reported by the RTC was before Tue Apr 19 2022 18:35:36 GMT+0000");
}


void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_timestamp);
    RUN_TEST(test_range);

    UNITY_END();
}

void loop() {

}