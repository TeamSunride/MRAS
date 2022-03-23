#include "FileSink.h"

FileSink::FileSink() {
	output_file.open("FileSink.out", std::ios::out | std::ios::trunc);
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	output_file << "Measurement started at: " << ctime(&now) << std::endl;
}

FileSink::FileSink(std::string filename) {
	output_file.open(filename, std::ios::out | std::ios::trunc);
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	output_file << "Measurement started at: " << ctime(&now) << std::endl;
}

FileSink::~FileSink() {
	output_file.close();
}

void FileSink::receive_measurement(Measurement in) {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	output_file << ctime(&now) << ":Recieved Measurement:" << "Type=";
	unsigned int count;
	float *val;
	switch (in.Type()) {
		case MeasurementType::Pressure:
			val = in.value(&count);
			output_file << "Pressure,Value=" << val[0] <<std::endl;
			break;
		case MeasurementType::Acceleration:
			val = in.value(&count);
			output_file << "Acceleration,Value=(x:" << val[0] << ", y:" << val[1] << ", z:" << val[2] << ")" << std::endl;
			break;
		case MeasurementType::GPS:
			val = in.value(&count);
			output_file << "GPS,Value=(Lat:" << val[0] << ", Lon:" << val[1] << ", alt:" << val[2] << ")" << std::endl;
			break;
		case MeasurementType::Magnetic_Field:
			val = in.value(&count);
			output_file << "Magnetic_Field,Value=(x:" << val[0] << ", y:" << val[1] << ", z:" << val[2] << ")" << std::endl;
			break;
		case MeasurementType::Rotation_Rate:
			val = in.value(&count);
			output_file << "RotationRate,Value=(i:" << val[0] << ", j:" << val[1] << ", k:" << val[2] << ", r:" << val[3] << ")" << std::endl;
			break;
		case MeasurementType::Temperature:
			val = in.value(&count);
			output_file << "Temperature,Value=" << val[0] <<std::endl;
			break;
	}
}
