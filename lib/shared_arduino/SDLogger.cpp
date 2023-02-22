//
// Created by Tom Danvers on 08/02/2023.
//

#include "SDLogger.h"

int8_t SDLogger::setup() {
    log("Starting SD card with CS Pin %d", SD_pin);

    if (SD.begin(SD_pin)) {
        log("SD card initialised");
    } else {
        log("SD card failed to initialise");
        return -1;
    }

    char log_filename[8] = "";
    // pick an appropriate file name
    for (int i = 0; i < 9999; i++) {
        sprintf(log_filename, "%d.csv", i);
        if (!SD.exists(log_filename)) {
            break;
        }
    }

    log("SD log filename: %s", log_filename);

    log_file = SD.open(log_filename, FILE_WRITE);

    setup_complete = true;
    return 0;
}
