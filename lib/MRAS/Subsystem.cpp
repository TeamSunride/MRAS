//
// Created by Tom Danvers on 13/12/2022.
//

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

void Subsystem::log(const char *text) {
    TextLogger* logger = MRAS_System::get_instance()->get_logger();
    if (logger != nullptr) {
        logger->_log(get_name(), text);
    }
}

void Subsystem::publish(SystemMessage *msg) {
    for (int i = 0; i < subscriber_count; i++) {
        Subsystem* subscriber = subscribers[i];
        subscriber->on_message(msg);
    }
}
