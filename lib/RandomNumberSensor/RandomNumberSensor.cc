#include "RandomNumberSensor.h"

RandomNumberSensor::RandomNumberSensor(MeasurementType type) : rng(dev()) {
	creation_type = type;
	dist = std::normal_distribution<float>(0, 2);
};


RandomNumberSensor::RandomNumberSensor() :
	creation_type(MeasurementType::Pressure),
	rng(dev()),
	dist(std::normal_distribution<float>(0, 2))
{};


void RandomNumberSensor::get_measurement() {
    if (creation_type == MeasurementType::Pressure ||
        creation_type == MeasurementType::Temperature) {
            output = Measurement(creation_type, dist(rng));
    } else if (creation_type != MeasurementType::Rotation_Rate) {
        output = Measurement(creation_type, dist(rng), dist(rng), dist(rng));
    } else {
        output = Measurement(creation_type, dist(rng), dist(rng), dist(rng), dist(rng));
	}
    propagate_result();
}

void RandomNumberSensor::receive_measurement(Measurement in) {
	input = in;
};
