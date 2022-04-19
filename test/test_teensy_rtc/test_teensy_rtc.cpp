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
    TEST_ASSERT_EQUAL(t2-t1, 1000);
}

void setup()
{
	UNITY_BEGIN();

    RUN_TEST(test_timestamp);

    UNITY_END();
}

void loop() {

}