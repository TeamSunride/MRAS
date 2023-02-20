// 10/02/2023 -- Nikilesh
#include "StateEstimator.h"


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
    altitude = rocket.get_altitude();
    return altitude;
}

void StateEstimator::on_message(SystemMessage *msg)
{
    if (msg->get_type() == BarometerDataMsg_t)
    {
        auto Nmsg = (BarometerDataMsg *) msg;
        log("Estimated altitude: %f", altitudeEstimate(Nmsg));
    }
    
}

StateEstimator::KalmanFilter::KalmanFilter(float delta, float accelStandardDeviation, float altimeterStandardDeviaiton)
{

    dt = delta;
    accelSTD = accelStandardDeviation;
    altimeterSTD = altimeterStandardDeviaiton;
    state << 0 , 0;
    covariance << 100, 0, 0, 100;
    stateTransitionMatrix << 1 , dt, 0, dt;
    controlMatrix << 0.5*(dt*dt) , dt;
    processNoise << (dt*dt*dt*dt)/4, (dt*dt*dt)/3, (dt*dt)/2, dt*dt;
    processNoise = processNoise * (accelSTD*accelSTD);
    observationMatrix << 1, 0;
    measurementVariance << altimeterSTD*altimeterSTD;
}

void StateEstimator::KalmanFilter::predict(AccelerometerDataMsg *accel)
{
    controlInput << (accel->acceleration[1] + g);

    state = stateTransitionMatrix * state + controlMatrix * controlInput;
    covariance = stateTransitionMatrix * covariance * stateTransitionMatrix.transpose() + processNoise;

}

void StateEstimator::KalmanFilter::update(BarometerDataMsg *pressure)
{
    innovationCovariance = observationMatrix * covariance * observationMatrix.transpose() + measurementVariance;
    kalmanGain = covariance * observationMatrix.transpose() * (1/innovationCovariance.determinant());

    state = state + kalmanGain* (altitude - observationMatrix * state);
    covariance = (Eigen::Matrix2f::Identity() - kalmanGain *observationMatrix) * covariance * (Eigen::Matrix2f::Identity() - kalmanGain *observationMatrix).transpose();
    // FIX THE ABOVE EQUATION TO SOLVE FOR COVARIANCE 
}