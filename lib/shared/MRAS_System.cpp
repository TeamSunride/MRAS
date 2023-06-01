//
// Created by Tom Danvers on 13/12/2022.
//

#include "MRAS_System.h"
#include "SystemMessage.h"
#include "system_messages/BuzzerMsg.h"

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
    bool overall_success = true;
    for (int i = 0; i < subsystem_count; i++) {
        Subsystem* system = subsystems[i];
        if (system->setup() != 0) {
            overall_success = false;
            buzzer->buzzer(NOTE_C6, 2000, true);
        }
    }

    if (overall_success) {
        buzzer->buzzer(NOTE_E6, 125, true);
        buzzer->buzzer(NOTE_G6, 125, true);
        buzzer->buzzer(NOTE_E7, 125, true);
        buzzer->buzzer(NOTE_C7, 125, true);
        buzzer->buzzer(NOTE_D7, 125, true);
        buzzer->buzzer(NOTE_G7, 125, true);
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

Subsystem *MRAS_System::get_buzzer() {
    return buzzer;
}

void MRAS_System::set_buzzer(Subsystem *_buzzer) {
    this->buzzer = _buzzer;
    add_subsystem(_buzzer);
}
