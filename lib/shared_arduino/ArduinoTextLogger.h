//
// Created by robos on 17/12/2022.
//

#ifndef MRAS_ARDUINOTEXTLOGGER_H
#define MRAS_ARDUINOTEXTLOGGER_H

#include "Arduino.h"
#include "TextLogger.h"
#include <cstdio>
#include <cstdarg>
#include "MRAS_Config.h"
#include "system_messages/TextLogMsg.h"

/**
 * @brief A TextLogger that logs to the Arduino Serial connection
 *
 * This class handles the setup of the Serial connection and the logging of messages to the Serial connection
 */
class ArduinoTextLogger : public TextLogger {
private:
    long _baud;
public:
    /**
     * @brief Construct a new Arduino Text Logger object
     *
     * @param id The ID of the logger
     * @param baud The baud rate of the Serial connection
     */
    explicit ArduinoTextLogger(uint8_t id, long baud) : TextLogger(id) {
        _baud = baud;
    };

    /**
     * @brief Log a message to the Arduino Serial connection
     *
     * @param fmt The format string
     * @param args The arguments to the format string
     */
    void _log(const char *fmt, va_list args) override;

    /**
     * @brief Set up the Serial connection
     *
     * @return int8_t 0 on success
     */
    int8_t setup() override {
        Serial.begin(_baud);
        log("Successfully set up Serial connection");
        Serial.println(MRAS_STARTUP_STRING);
        return 0;
    }

    /**
     * @brief Do nothing
     *
     * @return int8_t 0 on success
     */
    int8_t loop() override {
        return 0;
    }

    SUBSYSTEM_NAME("ArduinoTextLogger")
};


void ArduinoTextLogger::_log(const char *fmt, va_list args) {
    // https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro
    auto* msg = new TextLogMsg();
    vsprintf(msg->text, fmt, args);
    Serial.print(msg->text);
    publish(msg);
}

#endif //MRAS_ARDUINOTEXTLOGGER_H
