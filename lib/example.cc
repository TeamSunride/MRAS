#include <iostream>
#include "measurement.h"
#include "RandomNumberSensor.h"
#include "FileSink.h"
#include "node.h"
#include "Threshold_Filter.h"

#define ITERATIONS 10000

int main() {
	// setup part of the arduino code
	// initialize the nodes
	RandomNumberSensor rns(MeasurementType::Pressure);
	Threshold_Filter thresh_filter(3.0, MeasurementType::Pressure);
	FileSink output("test_out.txt");
	// connect the Nodes together
	rns.pass_result_to(&thresh_filter);
	thresh_filter.pass_result_to(&output);

	// the following part would be replaced with the loop of the arduino code
	for (int i=0; i < ITERATIONS; i++) {
		// as the rns is the only sensor that is initialized it's the only
		// function that is called in the 'loop'
		rns.get_measurement();
	}
	return 0;
}
