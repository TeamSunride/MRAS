//
// Created by Tom Danvers on 08/02/2023.
//

#include "SDLogger.h"

int8_t SDLogger::setup() {
    if (SD.begin(SD_pin)) {
        log("SD card initialised");
    } else {
        log("SD card failed to initialise");
        return -1;
    }

    char data_filename[8] = "";
    // pick an appropriate file name
    for (int i = 0; i < 9999; i++) {
        sprintf(data_filename, "%d.csv", i);
        if (!SD.exists(data_filename)) {
            break;
        }
    }

    log("SD data filename: %s", data_filename);

    data_file = SD.open(data_filename, FILE_WRITE);

    char log_filename[8] = "";
    // pick an appropriate file name
    for (int i = 0; i < 9999; i++) {
        sprintf(log_filename, "%d.log", i);
        if (!SD.exists(log_filename)) {
            break;
        }
    }

    log("SD log filename: %s", log_filename);

    log_file = SD.open(log_filename, FILE_WRITE);

    setup_complete = true;
    return 0;
}
