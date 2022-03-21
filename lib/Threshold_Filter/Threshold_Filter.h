//
// Created by Alexander Becker on 2022-03-20
// 2022 TeamSunride.
//

#ifndef _THRESHOLD_FILTER_H_
#define _THRESHOLD_FILTER_H_

#include "measurement.h"
#include "../common.h"

class Threshold_Filter {
public:
    void pass_result_to(void (*)(Measurement));
    void receive_measurement(Measurement);
    Threshold_Filter(const float threshold, const MeasurementType accepted_type);
private:
    bool filter();
    void propagate_result();
    float _threshold;
    Measurement input;
    Measurement output;
    MeasurementType _filtered_type;
    unsigned int registered_downstream_nodes;
    void (*child_nodes[MAX_DOWNSTREAM_NODES])(Measurement);
};

#endif
