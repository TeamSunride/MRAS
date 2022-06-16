//
// Created by Tom Danvers on 07/05/2022.
// 2022 TeamSunride.
//

#ifndef PAYLOAD_TYPES_H
#define PAYLOAD_TYPES_H

namespace downlink {
    enum PayloadType : uint8_t {
        UNDEFINED,
        Test_Payload_Type,
        DARTDebugPayload,
    };
}

#endif //PAYLOAD_TYPES_H
