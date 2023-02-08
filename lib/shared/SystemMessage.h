//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_SYSTEMMESSAGE_H
#define MRAS_SYSTEMMESSAGE_H

#include <cstdint>

enum SystemMessageType {
    UNDEFINED,
    AccelerometerDataMsg_t,
    HighGAccelerometerDataMsg_t,
    BarometerDataMsg_t,
    GyroDataMsg_t,
    MagnetometerDataMsg_t,
    GNSSDataMsg_t
};

class SystemMessage {
public:
    explicit SystemMessage(SystemMessageType type) : type(type) {};
    SystemMessageType get_type() { return type; };
protected:
    SystemMessageType type;
};

#endif //MRAS_SYSTEMMESSAGE_H