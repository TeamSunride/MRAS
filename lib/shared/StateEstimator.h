// 10/02/2023 -- Nikilesh
#include "Subsystem.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/MagnetometerDataMsg.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "Atmosphere.h"
#include "eigen.h"

class StateEstimator : public Subsystem
{
    public:
        explicit StateEstimator(uint8_t id) : Subsystem(id) {};
        using Subsystem::Subsystem;
        int8_t setup() override;
        int8_t loop() override;

        float altitudeEstimate(BarometerDataMsg *msg);
        void on_message(SystemMessage *msg) override;


        void initKF(float TimeDelta, float accelSTD, float altimeterSTD);
        void update(BarometerDataMsg *pressure);
        void predict(AccelerometerDataMsg *accel);

       // SUBSYSTEM_NO_MESSAGE_HANDLER;
        SUBSYSTEM_NAME("StateEstimator");
    
    private:
        float altitude = 0;
        float velocity = 0;
        // constants particular to a certain model
        float dt = 0;
        float accelSTD = 0;
        float altimeterSTD = 0;
        float g = -9.81;

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
        Eigen::Matrix<float, 1 ,1> innovationCovariance;
        Eigen::MatrixXf kalmanGain;
};

/*
class StateEstimator::KalmanFilter
{
    public:
        KalmanFilter(float delta, float accelStandardDeviation, float altimeterStandardDeviaiton);
        
        void update(BarometerDataMsg *pressure);
        void predict(AccelerometerDataMsg *accel);
        void getAlitudeEstimateKF();
        void getVelocityEstimateKF();
    private:
        // constants particular to a certain model
        float dt = 0;
        float accelSTD = 0;
        float altimeterSTD = 0;
        float g = -9.81;

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
        Eigen::MatrixXf innovationCovariance;
        Eigen::MatrixXf kalmanGain;



};
*/