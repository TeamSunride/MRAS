//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_TEXTLOGGER_H
#define MRAS_TEXTLOGGER_H


#include "../MRAS/Subsystem.h"
#include "../../../../../../.platformio/packages/toolchain-gccarmnoneeabi@1.50401.190816/arm-none-eabi/include/c++/5.4.1/cstdarg"

class TextLogger : public Subsystem {
public:
    using Subsystem::Subsystem;
    virtual void _log(const char *fmt, va_list args) = 0;
};

#endif //MRAS_TEXTLOGGER_H
