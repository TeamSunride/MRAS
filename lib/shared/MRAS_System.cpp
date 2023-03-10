//
// Created by Tom Danvers on 13/12/2022.
//

#include "MRAS_System.h"

MRAS_System* MRAS_System::instance = nullptr;

MRAS_System* MRAS_System::get_instance() {
    if(instance==nullptr){
        instance = new MRAS_System();
    }
    return instance;
}

bool MRAS_System::add_subsystem(Subsystem *subsystem) {
    if (subsystem_count < 254) {
        subsystems[subsystem_count] = subsystem;
        subsystem_count++;
        return true;
    } else {
        return false;
    }
}

void MRAS_System::setup() {
    for (int i = 0; i < subsystem_count; i++) {
        Subsystem* system = subsystems[i];
        system->setup();
    }
}

void MRAS_System::loop() {
    for (int i = 0; i < subsystem_count; i++) {
        Subsystem* system = subsystems[i];
        system->loop();
    }
}

void MRAS_System::set_logger(TextLogger *_logger) {
    logger = _logger;
    add_subsystem(logger);
}

TextLogger *MRAS_System::get_logger() {
    return logger;
}

#ifdef BUILD_ENV_rocket || BUILD_ENV_ground
void MRAS_System::set_buzzer(Buzzer *_buzzer) {
    buzzer = _buzzer;
    add_subsystem(buzzer);
}

Buzzer *MRAS_System::get_buzzer() {
    return buzzer;
}
#endif