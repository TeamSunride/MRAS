//
// Created by Tom Danvers on 11/03/2023.
//

#ifndef MRAS_TIMESTAMP_H
#define MRAS_TIMESTAMP_H

#include <Arduino.h>
#include <ctime>
#include <TimeLib.h>

uint64_t getTimestampMillis();

time_t getTeensy3Time();


#endif //MRAS_TIMESTAMP_H
