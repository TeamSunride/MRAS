//
// Created by Tom Danvers on 12/02/2022.
// 2022 TeamSunride.
//

#include "unity.h"
#include "serializers.h"

void test_struct_serialization() {
    typedef struct {
        int x, y, z;
    } packet_t;

    packet_t myPacket;
    myPacket.x = 1; myPacket.y = 2; myPacket.z = 3;

    uint8_t byteArray[sizeof(packet_t)];
    toByteArray<packet_t>(byteArray, myPacket);

    packet_t newPacket = fromByteArray<packet_t>(byteArray);

    TEST_ASSERT_EQUAL(myPacket.x, newPacket.x);
    TEST_ASSERT_EQUAL(myPacket.y, newPacket.y);
    TEST_ASSERT_EQUAL(myPacket.z, newPacket.z);
}

int main(int args, char **argv) {
    UNITY_BEGIN();

    RUN_TEST(test_struct_serialization);

    UNITY_END();

    return 0;
}