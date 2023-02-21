// 10/02/2023 -- Nikilesh
#include "Subsystem.h"
#include "LinearKalmanFilter.h"
#include "system_messages/StateEstimatorMsg.h"

class StateEstimator : public Subsystem
{
    public:
        explicit StateEstimator(uint8_t id) : Subsystem(id) {};
        using Subsystem::Subsystem;
        int8_t setup() override;
        int8_t loop() override;

        float altitudeEstimate(BarometerDataMsg *msg);
        void on_message(SystemMessage *msg) override;



       // SUBSYSTEM_NO_MESSAGE_HANDLER;
        SUBSYSTEM_NAME("StateEstimator");
    
    private:
        float altitude = 0;
        float velocity = 0;

        bool start = 0;
        bool recievedBaro = 0;
        bool recievedAcc = 0;
        
        float yAcceleration = 0;
        float pressure = 0;
        LinearKalmanFilter * Filter;
        AccelerometerDataMsg *acceleration;
        BarometerDataMsg *altimeter;
      
};

