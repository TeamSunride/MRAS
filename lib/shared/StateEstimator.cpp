// 10/02/2023 -- Nikilesh
#include "StateEstimator.h"


int8_t StateEstimator::setup()
{

   initKF(0.001, 28.7, 8.7);
   log("State Estimator initialized...");
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


void StateEstimator::initKF(float TimeDelta, float accelSTD, float altimeterSTD)
{
    dt = TimeDelta;
    accelSTD = accelSTD;
    altimeterSTD = altimeterSTD;
    state << 0 , 0;
    covariance << 100, 0, 0, 100;
    stateTransitionMatrix << 1 , dt, 0, dt;
    controlMatrix << 0.5*(dt*dt) , dt;
    processNoise << (dt*dt*dt*dt)/4, (dt*dt*dt)/3, (dt*dt)/2, dt*dt;
    processNoise = processNoise * (accelSTD*accelSTD);
    observationMatrix << 1, 0;
    measurementVariance << altimeterSTD*altimeterSTD;
}

void StateEstimator::predict(AccelerometerDataMsg *accel)
{
    controlInput << (accel->acceleration[2] + g);

    state = stateTransitionMatrix * state + controlMatrix * controlInput;
    covariance = stateTransitionMatrix * covariance * stateTransitionMatrix.transpose() + processNoise;   
    altitude = state(0,0);
    velocity = state(1,0); 
   // log("this is the state vel : %f", state(1,0));
}

void StateEstimator::update(BarometerDataMsg *pressure)
{
    innovationCovariance = observationMatrix * covariance * observationMatrix.transpose() + measurementVariance;
    float inC = innovationCovariance(0,0);
    kalmanGain = covariance * observationMatrix.transpose() * (1/inC);
    Atmosphere atmos(pressure->pressure);
    state = state + kalmanGain* ( atmos.get_altitude() - observationMatrix * state);
    covariance = (Eigen::Matrix2f::Identity() - kalmanGain *observationMatrix) * covariance * (Eigen::Matrix2f::Identity() - kalmanGain *observationMatrix).transpose() + kalmanGain* measurementVariance * kalmanGain.transpose();
    // FIX THE ABOVE EQUATION TO SOLVE FOR COVARIANCE --- done    
    // CHANGE BARO PRESSURE TO ALTITUDE
    altitude = state(0,0);
    velocity = state(1,0); 
}

/*
WHAT IF THE DATAMSG GET SWITCHED, AS IN THEY COME IN BAROMETERMSG, ACCEL, BARO, BARO
THIS WOULD MEAN IT WOULD DO PREDICT TWICE -- DOES THIS MAKE THE SYSTEM MORE ERROR PRONE??
*/


void StateEstimator::on_message(SystemMessage *msg)
{
    

    BarometerDataMsg * Nmsg;
    AccelerometerDataMsg * Acc;
    if (msg->get_type() == BarometerDataMsg_t)
    {
        Nmsg = (BarometerDataMsg *) msg;
        //log("Estimated altitude: %f", altitudeEstimate(Nmsg));
        update(Nmsg);

    } else if (msg->get_type() == AccelerometerDataMsg_t)
    {
        Acc = (AccelerometerDataMsg *) msg;
        log("Estimated altitude: %f ------- Estimated velocity: %f", altitude, velocity);
        predict(Acc);
    }

   
    
    
    //log("Estimated altitude: %f ------- Estimated velocity: %f", altitude, velocity);
    
}

/*

FACED WAY TOO MANY C++ ISSUES WITH THIS APPROACH SO AVOIDED AS I THOUGHT IT'S NOT WORTH THE EXTRA COMPLEXITY.

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
    covariance = (Eigen::Matrix2f::Identity() - kalmanGain *observationMatrix) * covariance * (Eigen::Matrix2f::Identity() - kalmanGain *observationMatrix).transpose() + kalmanGain* measurementVariance * kalmanGain.transpose();
    // FIX THE ABOVE EQUATION TO SOLVE FOR COVARIANCE 
}
*/