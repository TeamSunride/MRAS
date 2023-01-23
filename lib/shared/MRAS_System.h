//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_MRAS_SYSTEM_H
#define MRAS_MRAS_SYSTEM_H

#include "Subsystem.h"
#include "TextLogger.h"


class MRAS_System {
private:
    Subsystem* subsystems[255] = {};
    uint8_t subsystem_count = 0;
    static MRAS_System *instance;

    TextLogger* logger = nullptr;
public:

    /**
     * Singletons should not be cloneable
     */
    MRAS_System(MRAS_System &other) = delete;

    /**
     * Singletons should not be assignable
     */
    void operator=(const MRAS_System &) = delete;

    MRAS_System() = default;

    /**
     * This is the static method that controls the access to the singleton
     * instance. On the first run, it creates a singleton object and places it
     * into the static field. On subsequent runs, it returns the client existing
     * object stored in the static field.
     */
    static MRAS_System* get_instance();

    bool add_subsystem(Subsystem* subsystem);

    void setup();

    void loop();

    void set_logger(TextLogger *logger);

    TextLogger* get_logger();
};


#endif //MRAS_MRAS_SYSTEM_H
