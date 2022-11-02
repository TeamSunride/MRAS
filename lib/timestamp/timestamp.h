// Created by Ashley Shaw on 19/04/2022 using stuff from https://forum.pjrc.com/threads/68062-Teensy-4-1-RTC-get-milliseconds-correctly
// 2022 TeamSunride.
//


#ifndef TIMESTAMP_H
#define TIMESTAMP_H

#include <Arduino.h>
#include <time.h>
#include <TimeLib.h>



/**
 * @return UNIX time in milliseconds
 */
uint64_t getTimestampMillis();


time_t getTeensy3Time();


#endif //TIMESTAMP_H
