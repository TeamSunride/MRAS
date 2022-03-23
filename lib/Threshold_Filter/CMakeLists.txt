add_library(Threshold_Filter
	Threshold_Filter.cc
	Threshold_Filter.h)
target_link_libraries(Threshold_Filter
	Measurement
	Node)
