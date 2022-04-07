#ifndef _FILE_SINK_H_
#define _FILE_SINK_H_

#include "measurement.h"
#include <iostream>
#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>
#include "common.h"
#include "node.h"

class FileSink : public Node {
    public:
        FileSink();
		~FileSink();
        FileSink(std::string filename);
        void receive_measurement(Measurement) override;
    private:
		std::ofstream output_file;
};
#endif
