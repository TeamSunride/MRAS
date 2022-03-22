#ifndef _RANDOM_NUMBER_SENSOR_H_
#define _RANDOM_NUMBER_SENSOR_H_

#include <random>
#include "measurement.h"
#include "../common.h"

class RandomNumberSensor {
    public:
        bool pass_result_to(void (*)(Measurement));
        void get_measurement();
        RandomNumberSensor(MeasurementType);
        RandomNumberSensor();
    private:
        void propagate_result();
        Measurement output;
        MeasurementType creation_type;
        unsigned int registered_downstream_nodes;
        void (*dstr_nodes[MAX_DOWNSTREAM_NODES])(Measurement);
        float mean;
        float stdd;
        std::normal_distribution<float> dice;
		std::random_device dev;
        std::mt19937 rng;
};
#endif
