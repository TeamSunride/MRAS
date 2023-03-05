#include "SimulinkDataLogger.h"
#include "system_messages/StateEstimatorMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "Arduino.h"

int8_t SimulinkDataLogger::setup() {
    return 0;
}

int8_t SimulinkDataLogger::loop() {

    pressure.number = getFloat();
    yAccel.number = getFloat();
    // delay(1);
    float temperature = 15; // CHANGE IT LATER USE THE REAL VALUES
    auto *msg = new BarometerDataMsg();
    msg->pressure = pressure.number;
    msg->temperature = temperature;
    publish(msg);

    auto *Amsg = new AccelerometerDataMsg(AccelerometerDataMsg_t);
    Amsg->acceleration = {yAccel.number, yAccel.number, yAccel.number}; //CHANGE TO ALL REAL VALUES
    publish(Amsg);

    Serial.write('A');
    for (int i = 0; i < 4; i++)
    {
        Serial.write(position.bytes[i]);
    }
    for (int i = 0; i < 4; i++)
    {
        Serial.write(velocity.bytes[i]);
    }
    Serial.print("\n");
    delay(50);
    return 0;
}

void SimulinkDataLogger::on_message(SystemMessage   *msg) {
    
    switch (msg->get_type())
    {
    case StateEstimatorMsg_t: {

        auto state_msg = (StateEstimatorMsg *) msg;

        position.number = state_msg->estimatedAltitude;
        velocity.number = state_msg->estimatedVelocity;
        
        break;
    }
    default:
        break;
    }
    
    return;
}

float SimulinkDataLogger::getFloat(){
     int cont = 0;
    FLOATUNION_t f;
    while (cont < 4 ){
        f.bytes[cont] = Serial.read() ;
        cont = cont +1;
    }
    return f.number;
}