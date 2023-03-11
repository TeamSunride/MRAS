//
// Created by Tom Danvers on 13/12/2022.
//

#include <cstdarg>
#include <cstdio>
#include "Subsystem.h"
#include "MRAS_System.h"

uint8_t Subsystem::get_id() const {
    return id;
}

int8_t Subsystem::get_status() const {
    return status;
}

int8_t Subsystem::self_test() const {
    return self_test_result;
}

bool Subsystem::add_subscriber(Subsystem *subscriber) {
    if (subscriber_count < 254) {
        subscribers[subscriber_count] = subscriber;
        subscriber_count++;
        return true;
    } else {
        return false;
    }
}


void Subsystem::log(const char fmt[], ...) {
    // https://stackoverflow.com/questions/36881533/passing-va-list-to-other-functions
    TextLogger* logger = MRAS_System::get_instance()->get_logger();
    if (logger != nullptr) {
        char output[255] = {0};
        sprintf(output, "[%s] %s\n", get_name(), fmt);
        va_list args;
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wvarargs"
        va_start(args, output);
#pragma clang diagnostic pop
        logger->_log(output, args);
        va_end(args);

    }
}


void Subsystem::publish(SystemMessage *msg) {
    for (int i = 0; i < subscriber_count; i++) {
        Subsystem* subscriber = subscribers[i];
        subscriber->on_message(msg);
    }

    delete msg;
}

void Subsystem::buzzer(uint16_t frequency, uint32_t duration, bool block) {
    BuzzerInterface* buzzer = MRAS_System::get_instance()->get_buzzer();
    if (buzzer != nullptr) {
        buzzer->_buzzer(frequency, duration, block);
    }
}
