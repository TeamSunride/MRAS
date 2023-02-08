#include "Subsystem.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/MagnetometerDataMsg.h"
#include "Atmosphere.h"

class StateEstimator : public Subsystem
{
    public:
        using Subsystem::Subsystem;
        int8_t setup() override;
        int8_t loop() override;

        float altitude_estimate(BarometerDataMsg *msg);


        SUBSYSTEM_NAME("StateEstimator");
};