//
// Created by Tom Danvers on 12/12/2022.
//

#include <cstdio>

#include "Subsystem.h"
#include "MRAS_System.h"
#include "NativeTextLogger.h"

NativeTextLogger* logger = new NativeTextLogger(0);
MRAS_System* mras = MRAS_System::get_instance();

int main() {
    mras->set_logger(logger);

    mras->get_logger()->_log("Subsystem Name", "This is a log message");
    return 0;
}