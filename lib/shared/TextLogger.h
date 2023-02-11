//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_TEXTLOGGER_H
#define MRAS_TEXTLOGGER_H


#include "Subsystem.h"
#include <cstdarg>

/**
 * @brief A base class for ArduinoTextLogger and NativeTextLogger
 *
 * This class is used to provide a common interface for both ArduinoTextLogger and NativeTextLogger. This allows
 * either TextLogger to be used in the same way by MRAS and its Subsystems.
 */
class TextLogger : public Subsystem {
public:
    using Subsystem::Subsystem;

    SUBSYSTEM_NAME("TextLogger")
    SUBSYSTEM_NO_MESSAGE_HANDLER

    virtual void _log(const char *fmt, va_list args) = 0;
};

#endif //MRAS_TEXTLOGGER_H
