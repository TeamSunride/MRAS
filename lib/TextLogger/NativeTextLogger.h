//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_NATIVETEXTLOGGER_H
#define MRAS_NATIVETEXTLOGGER_H


#include "TextLogger.h"
#include <cstdio>
#include <cstdarg>

class NativeTextLogger : public TextLogger {
public:
    explicit NativeTextLogger(uint8_t id) : TextLogger(id) {};

    void _log(const char *fmt, va_list args) override;

    int8_t setup() override {
        log("Setting up %d", 123);
        return 0;
    }

    int8_t loop() override {
        log("Looping");
        return 0;
    }

    const char* get_name() override {
        return "NativeTextLogger";
    }
};

void NativeTextLogger::_log(const char *fmt, va_list args) {
    // https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro
    vprintf(fmt, args);
}


#endif //MRAS_NATIVETEXTLOGGER_H
