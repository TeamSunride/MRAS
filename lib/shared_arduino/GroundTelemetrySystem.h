//
// Created by Tom Danvers on 06/02/2023.
//

#ifndef MRAS_GROUNDTELEMETRYSYSTEM_H
#define MRAS_GROUNDTELEMETRYSYSTEM_H


#include "TelemetrySystem.h"

class GroundTelemetrySystem : public TelemetrySystem {
    using TelemetrySystem::TelemetrySystem;

    int8_t loop() override;
};


#endif //MRAS_GROUNDTELEMETRYSYSTEM_H
