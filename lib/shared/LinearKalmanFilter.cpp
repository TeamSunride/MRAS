#include "LinearKalmanFilter.h"

LinearKalmanFilter::LinearKalmanFilter(float TimeDelta, float STDacceleration, float STDaltimeter)
{
    dt = TimeDelta;
    accelSTD = STDacceleration;
    altimeterSTD = STDaltimeter;
    state << 0 , 0;
    covariance << 100, 0, 0, 100;
    stateTransitionMatrix << 1 , dt, 0, 1;
    controlMatrix << 0.5*(dt*dt) , dt;
    processNoise << (dt*dt*dt*dt)/4, (dt*dt*dt)/3, (dt*dt)/2, dt*dt;
    processNoise = processNoise * (accelSTD*accelSTD);
    observationMatrix << 1, 0;
    measurementVariance << altimeterSTD*altimeterSTD;
}

void LinearKalmanFilter::predict(float accel)
{
    controlInput << (accel + g);

    state = stateTransitionMatrix * state + controlMatrix * controlInput;
    covariance = stateTransitionMatrix * covariance * stateTransitionMatrix.transpose() + processNoise;   
    altitude = state(0,0);
    velocity = state(1,0); 
}

void LinearKalmanFilter::update(float pressure)
{
    innovationCovariance = observationMatrix * covariance * observationMatrix.transpose() + measurementVariance;
    inC = innovationCovariance(0,0);
    kalmanGain = covariance * observationMatrix.transpose() * (1/inC);
    Atmosphere atmos(pressure);
    state = state + kalmanGain* ( atmos.get_altitude() - observationMatrix * state);
    covariance = (Eigen::Matrix2f::Identity() - kalmanGain *observationMatrix) * covariance * (Eigen::Matrix2f::Identity() - kalmanGain *observationMatrix).transpose() + kalmanGain* measurementVariance * kalmanGain.transpose();
    // FIX THE ABOVE EQUATION TO SOLVE FOR COVARIANCE --- done    
    // CHANGE BARO PRESSURE TO ALTITUDE
    altitude = state(0,0);
    velocity = state(1,0); 
}

void LinearKalmanFilter::initialize(float alt, float vel) {
    state << alt, vel;
    covariance << 100, 0, 0, 100;
}
