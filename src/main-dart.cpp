//
// Created by Tom Danvers on 15/03/2022.
// 2022 TeamSunride.
// This file runs if the environment name does not correspond to any other main- file (aka, this is the default)
//

#include "Arduino.h"

#include "SimpleKalmanFilter.h"
#include "LineProtocolBuilder.h"
#include "global.h"
#include "timestamp.h"
#include "downlink.h"
#include "payloads/Test_Payload.h"
#include "serializers.h"
#include "dart_gpio.h"
#include "Wire.h"

// import sensors
#include "Barometer_MS5607.h"
#include "IMU_MPU6050.h"
#include "payloads/DARTDebugPayload.h"

// define sensors
Barometer *barometer = new Barometer_MS5607();
IMU *imu = new IMU_MPU6050();
Sensor *sensors[] = {barometer, imu};

// define filters
SimpleKalmanFilter pressureFilter = SimpleKalmanFilter(1, 1, 1);

void setup() {
    // set the Time library to use Teensy's RTC to keep time
    setSyncProvider(getTeensy3Time);

    setup_GPIO();

    flashRedLED(100);
    Serial.begin(115200);

    // begin I2C bus
    Wire.begin();

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
    uint32_t data_acq_start = millis();
    for (Sensor *sensor: sensors) {
        sensor->readData();
    }
    uint32_t data_acq_time = millis() - data_acq_start;

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
        DARTDebugPayload payload(
                imu->getAcceleration(),
                imu->getGyroVector());
        // add timestamp to payload
        payload.timestamp = getTimestampMillis();

        // create byte array to output data to radio
        uint8_t radioBuffer[sizeof payload];

        // convert payload to byte array for transmission
        toByteArray<DARTDebugPayload>(radioBuffer, payload);

        // transmit byte array containing payload data
        downlink::transmit(radioBuffer, sizeof radioBuffer);

        Serial.println("Transmitting payload: " + payload.toLineProtocol());
    }
}