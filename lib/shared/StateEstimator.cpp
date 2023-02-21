// 10/02/2023 -- Nikilesh
#include "StateEstimator.h"


int8_t StateEstimator::setup()
{
    Filter = new LinearKalmanFilter(0.001, 28, 8.7);
    log("State Estimator initialized...");
    return 0;
}

int8_t StateEstimator::loop()
{
    if (start == 0)
    {
        return 0;
    }

    // test --- success
    // Atmosphere obj(pressure);
    // log("SIMPLE ALT++++ %f", obj.get_altitude());

    Filter->predict(yAcceleration);
    Filter->update(pressure);
    altitude = Filter->get_altitude();
    velocity = Filter->get_velocity();
    log("logged alti ======= %f", altitude);
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

