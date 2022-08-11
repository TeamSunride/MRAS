//
// Created by Tom Danvers on 12/04/2022.
// 2022 TeamSunride.
//

#ifndef MRAS_LAUNCHDETECTOR_H
#define MRAS_LAUNCHDETECTOR_H

#include "Arduino.h"


class LaunchDetector {
public:
    /**
     * @param threshold The threshold which the magnitude of acceleration must surpass (m/s)
     * @param duration The duration in milliseconds for which the acceleration must be
     * above the threshold
     */
    LaunchDetector(const float &threshold, const uint32_t &duration);

    /**
     * Run the launch detector with a new z acceleration sample
     * @param z_acceleration Z-axis acceleration (longitudinal to the rocket) in m/s
     * @return Whether launch was detected or not
     */
    bool run(float z_acceleration);

    /**
     * Reset the internal timer and state
     */
    void reset();
private:
    float _threshold;
    uint32_t _duration;

    bool _above_threshold = false;
    uint32_t _start_time = 0;
};


#endif //MRAS_LAUNCHDETECTOR_H
