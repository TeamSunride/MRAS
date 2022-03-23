cmake_minimum_required(VERSION 3.0)
project(dummy-MRASv2)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories("${PROJECT_SOURCE_DIR}/include")

add_subdirectory(Measurement)
add_subdirectory(Node)
add_subdirectory(RandomNumberSensor)
add_subdirectory(FileSink)
add_subdirectory(Threshold_Filter)
add_subdirectory(Average_Filter)
add_subdirectory(Packet_Radio_Emulator)

add_executable(example-architecture
	example.cc)
target_link_libraries(example-architecture
	Measurement
	FileSink
	Threshold_Filter
	RandomNumberSensor
	Node)
