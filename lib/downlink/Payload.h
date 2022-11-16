//
// Created by Tom Danvers on 16/11/2022.
//

#ifndef MRAS_PAYLOAD_H
#define MRAS_PAYLOAD_H

#include <cstdint>

enum PayloadType : uint8_t {
    UNDEFINED,
    Test_Payload_t,
    DARTDebugPayload_t,
};

class Payload {
protected:
    PayloadType type = PayloadType::UNDEFINED;
public:
    PayloadType get_type() {
        return type;
    }
};

#endif //MRAS_PAYLOAD_H
