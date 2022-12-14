//
// Created by Tom Danvers on 12/12/2022.
//

#include <cstdio>

#include "MRAS_System.h"
#include "NativeTextLogger.h"

TextLogger* logger = new NativeTextLogger(0);
MRAS_System* mras = MRAS_System::get_instance();

int main() {
    mras->set_logger(logger);

    mras->get_logger()->_log("Hello world %s", "test");

    return 0;
}