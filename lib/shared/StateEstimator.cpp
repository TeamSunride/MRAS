// 10/02/2023 -- Nikilesh
#include "StateEstimator.h"
#include "system_messages/BarometerDataMsg.h"

int8_t StateEstimator::setup()
{
    return 0;
}

int8_t StateEstimator::loop()
{
    return 0;
}


float StateEstimator::altitudeEstimate(BarometerDataMsg *msg)
{
    Atmosphere rocket(msg->pressure);
    return rocket.get_altitude();
}

void StateEstimator::on_message(SystemMessage *msg)
{
    if (msg->get_type() == BarometerDataMsg_t)
    {
        auto Nmsg = (BarometerDataMsg *) msg;
        log("Estimated altitude: %f", altitudeEstimate(Nmsg));
    }
    
}