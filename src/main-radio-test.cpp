#include "Arduino.h"
#include "global.h"
#include "timestamp.h"
#include "downlink.h"
#include "serializers.h"
#include "Wire.h"
#include "buzzer.h"
#include "SD.h"

// import sensors
#include "Barometer_MS5607.h"
#include "IMU_MPU6050.h"
#include "GPS_ZOE_M8Q.h"
#include "Accelerometer_ADXL375.h"
#include "IMU_LSM_LIS.h"
#include "LSM6DSO32.h"
#include "LIS3MDL.h"

// import telemetry payloads
#include "payloads/Radio_Test_Payload.h"

#define SPI0_FREQUENCY  4000000

int packets_sent = 0;
int packets_logged = 0;
uint32_t last_packet_update = 0;


void setup() {

    downlink::setupRadio();

    // tell the radio to operate in explicit header mode for variable payload types
    downlink::radio.explicitHeader();

}

void loop() {

    // construct payload object for transmission
    uint32_t payload_size = 50;
    Radio_Test_Payload payload(payload_size);


    if (downlink::radioAvailable) {
        delay(1);
        // create byte array to output data to radio
        // convert payload to byte array for transmission

        // transmit byte array containing payload data
        downlink::transmit(payload.data, sizeof payload);
        packets_sent++;
    }

    if (millis() - last_packet_update > 100) {
        Serial.printf("Packets sent: %d,  Payload size:  %d\n", packets_sent, payload_size);

        packets_sent = 0;
        packets_logged = 0;
        last_packet_update = millis();
    }

}