// 10/02/2023 -- Nikilesh
#include "Subsystem.h"
#include "LinearKalmanFilter.h"
#include "system_messages/StateEstimatorMsg.h"
#include <Arduino.h>

#define THRESHOLD_VELOCITY 25 //ms^-1


class StateEstimator : public Subsystem
{
    public:
        explicit StateEstimator(uint8_t id, float tstep) : Subsystem(id) {
            Filter = new LinearKalmanFilter(tstep, 28, 8);
        };
        using Subsystem::Subsystem;
        int8_t setup() override;
        int8_t loop() override;

        static float altitudeEstimate(BarometerDataMsg *msg);
        void on_message(SystemMessage *msg) override;



       // SUBSYSTEM_NO_MESSAGE_HANDLER;
        SUBSYSTEM_NAME("StateEstimator");
    
    private:
        float altitude = 0;
        float velocity = 0;
        float prevAltitude = 0;
        uint8_t phase = 0;

        bool start = false;
        bool receivedBaro = false;
        bool receivedAcc = false;
        
        float yAcceleration = 0;
        float pressure = 0;

        // change this to uint32_t in future please @Nikilesh
        float currentMillis = 0;
        float prevMillis = 0;

        uint32_t last_log = 0;

        LinearKalmanFilter * Filter;
        AccelerometerDataMsg *acceleration{};
        BarometerDataMsg *altimeter{};
      
};

