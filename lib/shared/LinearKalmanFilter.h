#include "eigen.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "Atmosphere.h"

class LinearKalmanFilter {
public:
    LinearKalmanFilter(float TimeDelta, float STDacceleration, float STDaltimeter);

    void predict(float accel);

    void update(float pressure);

    float get_altitude() const { return altitude; }

    float get_velocity() const { return velocity; }

    float get_timeStep() const { return dt; }

private:
    float altitude = 0;
    float velocity = 0;
    // constants particular to a certain model
    float dt = 0;
    float accelSTD = 0;
    float altimeterSTD = 0;
    float g = -9.81;
    float inC = 0;
    // Matrices to be initialized
    Eigen::Matrix<float, 2, 1> state;
    Eigen::Matrix<float, 2, 2> covariance;
    Eigen::Matrix<float, 2, 2> stateTransitionMatrix;
    Eigen::Matrix<float, 2, 1> controlMatrix;
    Eigen::Matrix<float, 1, 1> controlInput;
    Eigen::Matrix<float, 2, 2> processNoise;
    Eigen::Matrix<float, 1, 2> observationMatrix;
    Eigen::Matrix<float, 1, 1> measurementVariance;

    // Matrices that are calculated
    Eigen::Matrix<float, 1, 1> innovationCovariance;
    Eigen::MatrixXf kalmanGain;
};
