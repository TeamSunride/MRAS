// 10/02/2023 -- Nikilesh
#include "Subsystem.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/MagnetometerDataMsg.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "Atmosphere.h"

class StateEstimator : public Subsystem
{
    public:
        explicit StateEstimator(uint8_t id) : Subsystem(id) {};
        using Subsystem::Subsystem;
        int8_t setup() override;
        int8_t loop() override;

        float altitudeEstimate(BarometerDataMsg *msg);

        SUBSYSTEM_NO_MESSAGE_HANDLER;
        SUBSYSTEM_NAME("StateEstimator");
};