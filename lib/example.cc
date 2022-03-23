#include <iostream>
#include "measurement.h"
#include "RandomNumberSensor.h"
#include "FileSink.h"
#include "node.h"
#include "Threshold_Filter.h"

#define ITERATIONS 10000

int main() {
	RandomNumberSensor rns(MeasurementType::Pressure);
	Threshold_Filter thresh_filter(3.0, MeasurementType::Pressure);
	FileSink output("test_out.txt");
	rns.pass_result_to(&thresh_filter);
	thresh_filter.pass_result_to(&output);
	for (int i=0; i < ITERATIONS; i++) {
		rns.get_measurement();
	}
	return 0;
}
