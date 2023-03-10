// Written by Nikilesh Ramesh -- 09/03/2023

#ifndef BUZZERINTERFACESYSTEM_H
#define BUZZERINTERFACESYSTEM_H

#include "Subsystem.h"

class Buzzer : public Subsystem
{
private:
    uint8_t buzzerPin = 10;
    uint16_t buzzerFreq = 1000;
public:
    Buzzer(uint8_t id) : Subsystem(id) {};
    int8_t setup();
    int8_t loop();
 
    void _buzz(uint32_t duration);

    SUBSYSTEM_NO_MESSAGE_HANDLER;
    SUBSYSTEM_NAME("Buzzer");
};


#endif