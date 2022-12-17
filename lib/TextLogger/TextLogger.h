//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_TEXTLOGGER_H
#define MRAS_TEXTLOGGER_H


#include "Subsystem.h"
#include <cstdarg>

class TextLogger : public Subsystem {
public:
    using Subsystem::Subsystem;

    void on_message(SystemMessage *msg) override {} // do nothing

    virtual void _log(const char *fmt, va_list args) = 0;
};

#endif //MRAS_TEXTLOGGER_H
