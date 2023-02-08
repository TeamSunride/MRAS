//
// Created by Tom Danvers on 06/02/2023.
//

#ifndef MRAS_ROCKETTELEMETRYSYSTEM_H
#define MRAS_ROCKETTELEMETRYSYSTEM_H


#include "TelemetrySystem.h"

class RocketTelemetrySystem : public TelemetrySystem {
    using TelemetrySystem::TelemetrySystem;

    int8_t loop() override;
};


#endif //MRAS_ROCKETTELEMETRYSYSTEM_H
