//
// Created by Tom Danvers on 08/02/2023.
//

#include "SDLogger.h"

int8_t SDLogger::setup() {
    if (SD.begin(BUILTIN_SDCARD)) {
        log("SD card initialised");
    } else {
        log("SD card failed to initialise");
        return -1;
    }

    char filename[8] = "";
    // pick an appropriate file name
    for (uint32_t i = 0; i < 65535; i++) {
        sprintf(filename, "%d.csv", i);
        if (!SD.exists(filename)) {
            break;
        }
    }

    log("SD filename: %s", filename);

    log_file = SD.open(filename, FILE_WRITE);

    return 0;
}

int8_t SDLogger::loop() {
    return 0;
}
