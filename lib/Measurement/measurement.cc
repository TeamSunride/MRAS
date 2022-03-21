#include "measurement.h"

Measurement::Measurement(MeasurementType in_type, float in_value) {
    _value[0] = in_value;
    type = in_type;
}

Measurement::Measurement(MeasurementType in_type, float v0, float v1, float v2) {
    type = in_type;
    _value[0] = v0;
    _value[1] = v1;
    _value[2] = v2;
}

float *Measurement::value(unsigned int *count) {
    if (type == MeasurementType::Pressure ||
        type == MeasurementType::Temperature) {
        *count = 1;
        return &_value[0];
    } else {
        *count = 3;
        return _value;
    }
}
MeasurementType Measurement::Type() {
    return type;
}
