// 12/02/2023 -- Nikilesh

#include "StateEstimator.h"
#include "unity.h"
#include "system_messages/BarometerDataMsg.h"

void setUp() {}

void tearDown() {}

float error = 0.02;

typedef struct msg
{
    float presssure;
    float temperature;
} Barometer;



void test_altitudeEstimate(void)
{
    auto* message = new Barometer;
    message->presssure = 101375;
    message->temperature = 15;
    auto Tmsg = (BarometerDataMsg *) message;
    StateEstimator obj(1);
    float altitude = obj.altitudeEstimate(Tmsg);

    TEST_ASSERT_TRUE(altitude - 0 > error);
    return;
}

int main()
{
    
    UNITY_BEGIN();
    RUN_TEST(test_altitudeEstimate);
    UNITY_END();
    return 0;
}