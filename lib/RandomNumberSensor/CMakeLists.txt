add_library(RandomNumberSensor
	RandomNumberSensor.cc
	RandomNumberSensor.h)
target_link_libraries(RandomNumberSensor
	Measurement
	Node)
