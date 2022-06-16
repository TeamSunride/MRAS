//
// Created by Tom Danvers on 12/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_GLOBAL_VARIABLES_H
#define MRASV2_GLOBAL_VARIABLES_H

#include "Barometer.h"

enum SystemState {
    IDLE,
    LAUNCH_DETECT,
    BURNOUT_DETECT,
    APOGEE_DETECT,
    ALTITUDE_DETECT,
    LANDING_DETECT
};

SystemState systemState = IDLE;

#endif //MRASV2_GLOBAL_VARIABLES_H