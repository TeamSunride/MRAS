//
// Created by Tom Danvers on 13/02/2022.
// 2022 TeamSunride.
//

#ifndef SERIALIZERS_H
#define SERIALIZERS_H

#include <stddef.h>
#include "stdint.h"

/**
 * Convert any data type to a byte array
 * @tparam input_type The input data type
 * @param outputByteArray The byte array to output the data to
 * @param inputData The data of type `input_type` to convert to a byte array
 */
template<typename input_type>
void toByteArray(uint8_t* outputByteArray, input_type inputData) {
    // create a pointer to the first byte of the struct in memory
    auto* startPtr = (uint8_t*)(&inputData);

    // increment the memory address for each byte in the struct and shove it into a byte array
    for (size_t i = 0; i < sizeof(inputData); i++) {
        outputByteArray[i] = *(startPtr + i);
    }
};

/**
 * Convert a byte array to any data type
 * @tparam output_type The type t output
 * @param byteArray The byte array to input
 * @return The resulting data of type `output_type`
 */
template<typename output_type>
output_type fromByteArray(const uint8_t* byteArray) {
    return *((output_type*) byteArray);
};

#endif //SERIALIZERS_H