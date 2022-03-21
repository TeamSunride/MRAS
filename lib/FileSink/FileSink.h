#ifndef _FILE_SINK_H_
#define _FILE_SINK_H_

#include "measurement.h"
#include <iostream>
#include <fstream>
#include <string>
#include "../common.h"

class FileSink {
    public:
        FileSink();
        FileSink(std::string filename);
        void receive_measurement(Measurement);
    private:
        ofstream output_file;
};
#endif