#ifndef _RANDOM_NUMBER_SENSOR_H_
#define _RANDOM_NUMBER_SENSOR_H_

#include <random>
#include "measurement.h"
#include "node.h"
#include "common.h"

class RandomNumberSensor : public Node {
    public:
        RandomNumberSensor(MeasurementType);
        RandomNumberSensor();
        void get_measurement();
        void receive_measurement(Measurement) override;
    private:
        MeasurementType creation_type;
        float mean;
        float stdd;
        std::normal_distribution<float> dist;
		std::random_device dev;
        std::mt19937 rng;
};
#endif
