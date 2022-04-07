//
// Created by Alexander Becker on 2022-03-20
// 2022 TeamSunride.
//

#ifndef _THRESHOLD_FILTER_H_
#define _THRESHOLD_FILTER_H_

#include "measurement.h"
#include "node.h"
#include "common.h"

class Threshold_Filter: public Node {
public:
    Threshold_Filter(const float threshold, const MeasurementType accepted_type);
    void receive_measurement(Measurement) override;
private:
    bool filter();
    float _threshold;
    MeasurementType _filtered_type;
};

#endif
