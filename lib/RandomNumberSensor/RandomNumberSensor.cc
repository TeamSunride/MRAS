#include "RandomNumberSensor.h"

RandomNumberSensor::RandomNumberSensor(MeasurementType type) {
    creation_type = type;
}

RandomNumberSensor::RandomNumberSensor() {
    creation_type = MeasurementType::Pressure;
}

void RandomNumberSensor::propagate_result() {
    for (unsigned int i = 0; i < registered_downstream_nodes; i++) {
        dstr_nodes[i](output);
    }
}

void RandomNumberSensor::get_measurement() {
    if (creation_type == MeasurementType::Pressure ||
        creation_type == MeasurementType::Temperature) {
            output = Measurement(creation_type, dist(rng));
    } else {
        output = Measurement(creation_type, dist(rng), dist(rng), dist(rng));
    }
    propagate_result();
}

bool RandomNumberSensor::pass_result_to(void (*dwnstr_node))(Measurement)) {
    if (registered_downstream_nodes < MAX_DOWNSTREAM_NODES) {
        dwnstr_nodes[registered_downstream_nodes] = dwnstr_node;
        registered_downstream_nodes ++;
        return true;
    }
    return false;
}