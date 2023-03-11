// 12/02/2023 -- Nikilesh

/**
 * Comment from Tom when merging with main branch, 10/03/2023:
 *
 * This test is not working. I have commented it out for now.
 *
 * This is because the StateEstimator has moved to the shared_arduino library and the test runs on the native platform.
 *
 * If required please run the test on hardware rather than native (ie teensy) otherwise it can be discarded if this
 * test is no longer used.
 */

//#include "StateEstimator.h"
#include "unity.h"
//#include "system_messages/BarometerDataMsg.h"
//
void setUp() {}

void tearDown() {}
//
//float error = 0.02;
//
//typedef struct msg
//{
//    float presssure;
//    float temperature;
//} Barometer;
//
//
//
//void test_altitudeEstimate(void)
//{
//    auto* message = new Barometer;
//    message->presssure = 101375;
//    message->temperature = 15;
//    auto Tmsg = (BarometerDataMsg *) message;
//    StateEstimator obj(1);
//    float altitude = obj.altitudeEstimate(Tmsg);
//
//    TEST_ASSERT_TRUE(altitude - 0 > error);
//    return;
//}
//
int main()
{

    UNITY_BEGIN();
//    RUN_TEST(test_altitudeEstimate);
    UNITY_END();
    return 0;
}