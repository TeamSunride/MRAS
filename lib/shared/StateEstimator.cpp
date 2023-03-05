// 10/02/2023 -- Nikilesh
#include "StateEstimator.h"


int8_t StateEstimator::setup()
{
    Filter = new LinearKalmanFilter(0.05, 28, 2);
    log("State Estimator initialized...");
#ifdef BUILD_ENV_rocket
    currentMillis = millis();
#endif
    return 0;
}

int8_t StateEstimator::loop()
{
    if (start == 0)
    {
        return 0;
    }
#ifdef BUILD_ENV_rocket
    if ((currentMillis - prevMillis)/1000 < Filter->get_timeStep())
    {
        return 0;
    }
#endif
    Filter->predict(yAcceleration);
    Filter->update(pressure);
    altitude = Filter->get_altitude();
    velocity = Filter->get_velocity();
    //log("logged alti ======= %f", altitude);
    auto stateMsg = new StateEstimatorMsg();
    stateMsg->estimatedAltitude = altitude;
    stateMsg->estimatedVelocity = velocity;
    publish(stateMsg);

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
        altimeter = (BarometerDataMsg *) msg;
        pressure = altimeter->pressure;
        // log("pressure +++++ %f", pressure); // debug
        recievedBaro = 1;

    } else if (msg->get_type() == AccelerometerDataMsg_t)
    {
        acceleration = (AccelerometerDataMsg *) msg;
        yAcceleration = acceleration->acceleration[1];
        recievedAcc = 1;

    }  

    if (recievedBaro == 1 && recievedAcc == 1)
    {
        start = 1;
    }
    
}

