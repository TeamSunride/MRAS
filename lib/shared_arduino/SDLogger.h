//
// Created by Tom Danvers on 08/02/2023.
//

#ifndef MRAS_SDLOGGER_H
#define MRAS_SDLOGGER_H


#include "Subsystem.h"
#include "Arduino.h"
#include "SD.h"

/**
 * @brief General SD logger class, used by both the ground and rocket SD loggers. This class is not intended to be used
 * directly. Instead, use the RocketSDLogger or GroundSDLogger classes.
 *
 * This class contains the setup function for the SD card and stores the log file.
 *
 * The RocketSDLogger and GroundSDLogger classes contain the loop and on_message functions for logging data.
 */
class SDLogger : public Subsystem {
public:
    /**
     * @brief Construct a new SDLogger object
     *
     * @param id The ID of the subsystem
     * @param sdPin The chip select pin the SD card is connected to
     */
    SDLogger(uint8_t id, uint8_t sdPin) : Subsystem(id) {
        SD_pin = sdPin;
    }
private:
    uint8_t SD_pin;

    SUBSYSTEM_NAME("SDLogger")

    int8_t setup() override;

protected:
    File log_file;
    bool setup_complete = false;
};


#endif //MRAS_SDLOGGER_H
