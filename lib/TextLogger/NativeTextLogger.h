//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_NATIVETEXTLOGGER_H
#define MRAS_NATIVETEXTLOGGER_H


#include "TextLogger.h"
#include <cstdio>

class NativeTextLogger : public TextLogger {
public:
    explicit NativeTextLogger(uint8_t id) : TextLogger(id) {};

    void _log(const char* text) override;
    void _log(const char *name, const char *text) override;

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

void NativeTextLogger::_log(const char *text) {
    printf("%s\n", text);
}

void NativeTextLogger::_log(const char* name, const char *text) {
    printf("[%s] %s\n", name, text);
}


#endif //MRAS_NATIVETEXTLOGGER_H
