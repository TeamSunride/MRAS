//
// Created by Tom Danvers on 12/04/2022.
// 2022 TeamSunride.
//

#include "LaunchDetector.h"

LaunchDetector::LaunchDetector(const float &threshold, const uint32_t &duration) {
    _threshold = abs(threshold);
    _duration = duration;
}

bool LaunchDetector::run(float z_acceleration) {
    if (abs(z_acceleration) >= _threshold) {
        if (_above_threshold) {
            // if we have been above the threshold for the desired time, detect launch
            if (millis() - _start_time > _duration) {
                return true;
            }
        } else {
            // if we were not already above the threshold, start the timer
            _start_time = millis();
        }

        _above_threshold = true;
    } else {
        _above_threshold = false;
    }

    return false;
}

void LaunchDetector::reset() {
    _above_threshold = false;
    _start_time = 0;
}
