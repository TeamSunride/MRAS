//
// Created by robos on 17/12/2022.
//

#ifndef MRAS_ARDUINOTEXTLOGGER_H
#define MRAS_ARDUINOTEXTLOGGER_H

#include "Arduino.h"
#include "TextLogger.h"
#include <cstdio>
#include <cstdarg>

class ArduinoTextLogger : public TextLogger {
private:
    long _baud;
public:
    explicit ArduinoTextLogger(uint8_t id, long baud) : TextLogger(id) {
        _baud = baud;
    };

    void _log(const char *fmt, va_list args) override;

    int8_t setup() override {
        Serial.begin(_baud);
        log("Successfully set up Serial connection");
        return 0;
    }

    int8_t loop() override {
        return 0;
    }

    const char* get_name() override {
        return "ArduinoTextLogger";
    }
};

void ArduinoTextLogger::_log(const char *fmt, va_list args) {
    // https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro
    char buffer[255] = {};
    vsprintf(buffer, fmt, args);
    Serial.print(buffer);
}

#endif //MRAS_ARDUINOTEXTLOGGER_H
