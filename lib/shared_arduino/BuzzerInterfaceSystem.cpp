// Written by Nikilesh Ramesh 09/03/2023

#include "BuzzerInterfaceSystem.h"
#include "system_messages/BuzzerMsg.h"
#include "Arduino.h"


int8_t Buzzer::setup() 
{
    pinMode(buzzerPin, OUTPUT);
    return 0;
}

int8_t Buzzer::loop() 
{
    return 0;
}


void Buzzer::_buzz(uint32_t duration)
{
    tone(buzzerPin, buzzerFreq, duration);
    log("&&&&&&   BUZZED BUZZZED BUZZZED &&&&&&&");
}