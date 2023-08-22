#include "SimulinkDataLogger.h"
#include "system_messages/StateEstimatorMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "Arduino.h"
#include "system_messages/GyroDataMsg.h"

int8_t SimulinkDataLogger::setup() {
    return 0;
}

int8_t SimulinkDataLogger::loop() {

    switch (_mode) {
        case 1: {
            while (!Serial.available()) {} // IMPORTANT: else it breaks the HIL
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
            for (unsigned char byte: position.bytes) {
                Serial.write(byte);
            }
            for (unsigned char byte: velocity.bytes) {
                Serial.write(byte);
            }
            Serial.print("\n");
            delay(50);
        }
        case 2: {
            //while (!Serial.available()){} // IMPORTANT: else it breaks the HIL
            Serial.write('A');
            for (unsigned char byte: gyroX.bytes) {
                Serial.write(byte);
            }
            for (unsigned char byte: gyroY.bytes) {
                Serial.write(byte);
            }
            for (unsigned char byte: gyroZ.bytes) {
                Serial.write(byte);
            }
            Serial.print("\n");
            //Serial.printf("%f,%f,%f\n", gyroX.number, gyroY.number, gyroZ.number);
            delay(50);
        }
        case 3: {
            Serial.write('A');
            for (unsigned char byte: q1.bytes) {
                Serial.write(byte);
            }
            for (unsigned char byte: q2.bytes) {
                Serial.write(byte);
            }
            for (unsigned char byte: q3.bytes) {
                Serial.write(byte);
            }
            for (unsigned char byte: q4.bytes) {
                Serial.write(byte);
            }
            Serial.print("\n");
            //Serial.printf("%f,%f,%f,%f\n", q1.number, q2.number, q3.number, q4.number);
            delay(50);
        }
    }
    return 0;
}

void SimulinkDataLogger::on_message(SystemMessage *msg) {

    switch (msg->get_type()) {
        case StateEstimatorMsg_t: {

            auto state_msg = (StateEstimatorMsg *) msg;

            position.number = state_msg->estimatedAltitude;
            velocity.number = state_msg->estimatedVelocity;

            break;
        }
        case GyroDataMsg_t: {

            auto gyro_msg = (GyroDataMsg *) msg;

            gyroX.number = gyro_msg->gyro[0];
            gyroY.number = gyro_msg->gyro[1];
            gyroZ.number = gyro_msg->gyro[2];
            //log("%f,%f,%f", gyroX.number, gyroY.number, gyroZ.number);
            break;
        }
        case OrientationDataMsg_t: {

            auto orientation_msg = (OrientationDataMsg *) msg;

            q1.number = orientation_msg->quaternion[0];
            q2.number = orientation_msg->quaternion[1];
            q3.number = orientation_msg->quaternion[2];
            q4.number = orientation_msg->quaternion[3];

            break;
        }
        default:
            break;
    }

}

float SimulinkDataLogger::getFloat() {
    int cont = 0;
    FLOATUNION_t f;
    while (cont < 4) {
        f.bytes[cont] = Serial.read();
        cont = cont + 1;
    }
    return f.number;
}