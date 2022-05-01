//
// Created by Tom Danvers on 24/04/2022.
// 2022 TeamSunride.
//

#include "unity.h"
#include "downlink.h"
#include "serializers.h"

enum PayloadType {
    A,
    B
};

struct PayloadA {
    PayloadType type = A;
    int x = 1;
    int y = 2;
    int z = 3;

    // define equality operator to make stuff easier later
    bool operator==(PayloadA& p) const {
        if(this == &p) return true; //This is the pointer for

        return x == p.x && y == p.y && z == p.z;
    }
};

struct PayloadB {
    PayloadType type = B;
    int x = 1;
    int y = 2;
    int z = 3;
    float latitude = 55;
    float longitude = 56;

    // define equality operator to make stuff easier later
    bool operator==(PayloadB& p) const {
        if(this == &p) return true; //This is the pointer for
        return x == p.x && y == p.y && z == p.z && latitude == p.latitude && longitude == p.longitude;
    }
};

PayloadA payloadA;
PayloadB payloadB;
PayloadA receivedPayloadA;
PayloadB receivedPayloadB;


void test_radio_setup() {
    TEST_ASSERT_EQUAL_MESSAGE(0, downlink::setupRadio(), "Radio failed to start - view here for status codes "
                                                         "https://jgromes.github.io/RadioLib/group__status__codes.html");

    TEST_ASSERT_EQUAL_MESSAGE(RADIOLIB_ERR_NONE, downlink::radio.explicitHeader(), "Failed to enter explicit header mode");
}

void test_payloadA_equality() {
    TEST_ASSERT_TRUE(payloadA == receivedPayloadA)
}

void test_payloadB_equality() {
    TEST_ASSERT_TRUE(payloadB == receivedPayloadB)
}

void setup() {
    // Wait for Serial connection before starting test
    Serial.begin(115200);
    while (!Serial) {}

    UNITY_BEGIN();


    RUN_TEST(test_radio_setup);

    // if this is the transmitter, end the test here and move on to the main loop
#if TEST_RADIO_ROCKET
    UNITY_END();
#elif TEST_RADIO_GROUND
    downlink::receive();  // start receiving
#endif

}

PayloadType lastPayloadType;
uint8_t radioBuffer[sizeof(PayloadA) + sizeof (PayloadB) + 1]; // big enough to house more than what we need

uint8_t iterations;

void loop() {
#if TEST_RADIO_ROCKET // this is the transmitter environment
    if (!downlink::radioAvailable) return;

    memset(radioBuffer, 0, sizeof radioBuffer);

    size_t transmitSize;

    switch (lastPayloadType) {
        case A:
            toByteArray<PayloadB>(radioBuffer, payloadB);
            transmitSize = sizeof(PayloadB);
            lastPayloadType = B;
            break;
        case B:
            toByteArray<PayloadA>(radioBuffer, payloadA);
            transmitSize = sizeof(PayloadA);
            lastPayloadType = A;
            break;
    }

    downlink::transmit(radioBuffer, transmitSize);

    delay(1000);
#elif TEST_RADIO_GROUND
    if (!downlink::radioAvailable) return;

    memset(radioBuffer, 0, sizeof radioBuffer);

    // output all data into the buffer. Setting `len` to zero retrieves the packet length automatically
    downlink::radio.readData(radioBuffer, 0);

    // determine which payload type was received by reading the first byte
    auto receivedPayloadType = static_cast<PayloadType>(radioBuffer[0]);

    // clear payload stores so the test is valid
    memset(&receivedPayloadA, 0, sizeof receivedPayloadA);
    memset(&receivedPayloadB, 0, sizeof receivedPayloadB);

    switch (receivedPayloadType) {
        case A:
            receivedPayloadA = fromByteArray<PayloadA>(radioBuffer);
            RUN_TEST(test_payloadA_equality);
            break;
        case B:
            receivedPayloadB = fromByteArray<PayloadB>(radioBuffer);
            RUN_TEST(test_payloadB_equality);
            break;
    }

    iterations++;

    if (iterations > 10) {
        UNITY_END();
    }

    downlink::receive();


#endif
}
