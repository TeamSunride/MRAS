//
// Created by Tom Danvers on 15/03/2022.
// 2022 TeamSunride.
// This file runs if the environment name does not correspond to any other main- file (aka, this is the default)
//

#include "Arduino.h"
#include "global.h"
#include "timestamp.h"
#include "downlink.h"
#include "serializers.h"
#include "Wire.h"

// import sensors
#include "Barometer_MS5607.h"
#include "IMU_MPU6050.h"
#include "GPS_ZOE_M8Q.h"
#include "Accelerometer_ADXL375.h"

// import telemetry payloads
#include "payloads/DARTDebugPayload.h"

// define sensors (specific hardware)
Barometer_MS5607 ms5607 = Barometer_MS5607(0x76, &Wire2);
IMU_MPU6050 mpu6050 = IMU_MPU6050();
GPS_ZOE_M8Q zoe_m8q = GPS_ZOE_M8Q();
Accelerometer_ADXL375 adxl375 = Accelerometer_ADXL375(&Wire2, 0x53);

// define sensors (interfaces)
Barometer *barometer = &ms5607;
IMU *imu = &mpu6050;
GPS *gps = &zoe_m8q;
Accelerometer *accelerometer = &adxl375;

Sensor *sensors[] = {barometer, imu, gps, accelerometer};


void setup() {
    // set the Time library to use Teensy's RTC to keep time
    setSyncProvider(getTeensy3Time);

    Serial.begin(115200);

    // begin I2C bus
    Wire.begin();
    Wire2.begin();

    downlink::setupRadio();

    // tell the radio to operate in explicit header mode for variable payload types
    downlink::radio.explicitHeader();

    // init all sensors
    for (Sensor *sensor: sensors) {
        sensor->begin();
    }
}

void loop() {
    // Read data from sensors
    uint32_t DAQStart = millis();
    for (Sensor *sensor: sensors) {
        sensor->readData();
    }
    uint32_t DAQTime = millis() - DAQStart;

    switch (systemState) {
        case IDLE:
            // check for command / switch to enter LAUNCH_DETECT state
            break;
        case LAUNCH_DETECT:
            // run Launch Detector
            break;
        case BURNOUT_DETECT:
            // we might skip this state for DART 2022
        case APOGEE_DETECT:
            // run apogee detector and then deploy drogue chute
            break;
        case ALTITUDE_DETECT:
            // run altitude detector and then deploy main chute
            break;
        case LANDING_DETECT:
            // detect that the rocket has landed and switch back to idle mode
            break;
    }

    if (downlink::radioAvailable) {
        // construct payload object for transmission
        DARTDebugPayload payload(imu, gps, barometer, accelerometer);
        // add timestamp to payload
        payload.timestamp = getTimestampMillis();
        payload.DAQTime = DAQTime > 255 ? 255 : DAQTime;

        // create byte array to output data to radio
        uint8_t radioBuffer[sizeof payload];

        // convert payload to byte array for transmission
        toByteArray<DARTDebugPayload>(radioBuffer, payload);

        // transmit byte array containing payload data
        downlink::transmit(radioBuffer, sizeof radioBuffer);

        char output_string[512];
        payload.toLineProtocol(output_string);
        Serial.println(output_string);
    }
}