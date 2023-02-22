//
// Created by Tom Danvers on 17/02/2023.
//

#include "unity.h"
#include "cobs_encoding.h"
#include <cstdio>

void setUp() {}

void tearDown() {}

void print_buffer(uint8_t *buffer, size_t length) {
    for (int i = 0; i < length; i++) {
        printf("%d ", buffer[i]);
    }
    printf("\n");
}

void test_cobs_encoding() {
    uint8_t encoded_buffer[255] = {};
    uint8_t decoded_buffer[255] = {};
    uint8_t input_data[] = {1, 0, 3, 4, 5, 0, 1};

    printf("Input data: \t");
    print_buffer(input_data, sizeof input_data);

    uint8_t encoded_length = cobsEncode(input_data, sizeof input_data, encoded_buffer);

    printf("Encoded data: \t");
    print_buffer(encoded_buffer, encoded_length);

    uint8_t decoded_length = cobsDecode(encoded_buffer, encoded_length, decoded_buffer);

    printf("Decoded data: \t");
    print_buffer(decoded_buffer, decoded_length);

    TEST_ASSERT_EQUAL_UINT8_ARRAY(input_data, decoded_buffer, sizeof input_data);
}

int main() {
    UNITY_BEGIN();

    RUN_TEST(test_cobs_encoding);

    UNITY_END();
}