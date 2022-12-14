//
// Created by robos on 14/12/2022.
//

#ifndef RADIO_TEST_PAYLOAD_H
#define RADIO_TEST_PAYLOAD_H

#include "downlink.h"
#include "LineProtocolBuilder.h"
#include "Payload.h"

class Radio_Test_Payload : public Payload {
public:
    uint8_t *data;

    Radio_Test_Payload() = default;

    explicit Radio_Test_Payload(uint32_t size) {
        data = new uint8_t[size];
        for (int i = 0; i < size; i++) {
            data[i] = i;
        }
    }


    ~Radio_Test_Payload() {
        delete[] data;
    }
};





#endif //RADIO_TEST_PAYLOAD_H
