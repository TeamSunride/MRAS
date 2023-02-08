
#include "StateEstimator.h"

int8_t StateEstimator::setup()
{
    return 0;
}

int8_t StateEstimator::loop()
{
    return 0;
}

float StateEstimator::altitude_estimate(BarometerDataMsg *msg)
{
    Atmosphere rocket(msg->pressure);
    return rocket.get_altitude();
}