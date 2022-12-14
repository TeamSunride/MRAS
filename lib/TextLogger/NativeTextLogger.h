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

    void _log(const char *fmt, ...) override;

    int8_t setup() override {
        log("Setting up");
        return 0;
    }

    int8_t loop() override {
        return 0;
    }

    const char* get_name() override {
        return "NativeTextLogger";
    }
};

void NativeTextLogger::_log(const char *fmt, ...) {
    // https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
    printf("\n");
    va_end(args);
}


#endif //MRAS_NATIVETEXTLOGGER_H
