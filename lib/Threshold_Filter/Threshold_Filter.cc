//
// Created By Alexander Becker 2022-03-20
// 2022 TeamSunride.
//
#include "Threshold_Filter.h"
#include <math.h>

Threshold_Filter::Threshold_Filter(const float threshold, const MeasurementType accepted_type) {
    _threshold = threshold;
    _filtered_type = accepted_type;
    registered_downstream_nodes = 0;
}

void Threshold_Filter::pass_result_to(void (*dstr_handle)(Measurement)) {
    if (registered_downstream_nodes == MAX_DOWNSTREAM_NODES)
        return;
    child_nodes[registered_downstream_nodes] = dstr_handle;
    registered_downstream_nodes ++;
}

void Threshold_Filter::propagate_result() {
    for (unsigned int i = 0; i < registered_downstream_nodes; i++) {
        child_nodes[i](output);
    }
}

bool Threshold_Filter::filter() {
    unsigned int vcount = 0;
    float *data = input.value(&vcount);
    if (vcount == 1) {
        if (data[0] > _threshold) {
            output = Measurement(input.Type(), data[0]);
            return true;
        }
        return false;
    } else if (vcount == 3) {
        float mag = sqrt(pow(data[0], 2) + pow(data[1], 2) + pow(data[2], 2));
        if (mag > _threshold) {
            output = Measurement(input.Type(), data[0], data[1], data[2]);
            return true;
        }
        return false;
    } else {
        return false;
    }
}

void Threshold_Filter::receive_measurement(Measurement in) {
    if (in.Type() != _filtered_type)
        return;
    input = in;
    if (filter()) 
        propagate_result();
}