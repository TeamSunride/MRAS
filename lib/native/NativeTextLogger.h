//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_NATIVETEXTLOGGER_H
#define MRAS_NATIVETEXTLOGGER_H


#include "TextLogger.h"
#include "MRAS_Config.h"
#include "system_messages/TextLogMsg.h"
#include <cstdio>
#include <cstdarg>

/**
 * @brief A TextLogger that is compatible with the Native MRAS build environment
 *
 * In the native build environment, we can use printf to log to the console
 */
class NativeTextLogger : public TextLogger {
public:
    explicit NativeTextLogger(uint8_t id) : TextLogger(id) {};

    /**
     * @brief Log a message to the console
     *
     * @param fmt The format string
     * @param args The arguments to the format string
     */
    void _log(const char *fmt, va_list args) override;

    int8_t setup() override {
        log("Setup...");
        printf(MRAS_STARTUP_STRING);
        return 0;
    }

    int8_t loop() override {
        return 0;
    }

    const char* get_name() override {
        return "NativeTextLogger";
    }
};

void NativeTextLogger::_log(const char *fmt, va_list args) {
    // https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro
    auto* msg = new TextLogMsg();
    vsprintf(msg->text, fmt, args);
    printf("%s", msg->text);
    publish(msg);
}


#endif //MRAS_NATIVETEXTLOGGER_H
