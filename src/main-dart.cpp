//
// Created by Tom Danvers on 15/03/2022.
// 2022 TeamSunride.
// This file runs if the environment name does not correspond to any other main- file (aka, this is the default)
//

#include "Arduino.h"
#include "Barometer.h"
#include "Barometer_MS5607.h"
#include "SimpleKalmanFilter.h"
#include "LineProtocolBuilder.h"
#include "global_variables.h"
#include "timestamp.h"
#include "downlink.h"
#include "payloads/Test_Payload.h"
#include "serializers.h"

// define sensors
Barometer *barometer = new Barometer_MS5607();
Sensor *sensors[] = {barometer};

// define filters
SimpleKalmanFilter pressureFilter = SimpleKalmanFilter(1, 1, 1);

void setup() {
    Serial.begin(115200);
    downlink::setupRadio();

    // tell the radio to operate in explicit header mode for variable payload types
    downlink::radio.explicitHeader();

    // set the Time library to use Teensy's RTC to keep time
    setSyncProvider(getTeensy3Time);

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

    // do processing with resulting data
    float measured_pressure = barometer->getPressure();
    float filtered_pressure = pressureFilter.updateEstimate(measured_pressure);
    /*
    Serial.println(
            LineProtocolBuilder("pressureTest")
            .addField("measuredPressure", measured_pressure)
            .addField("filteredPressure", filtered_pressure)
            .addField("daqTime", (int64_t) data_acq_time)
            .setTimestamp(getTimestampMillis())
            .build());
            */

    switch (system_state) {
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
        Test_Payload payload(1, 2, 3);
        // add timestamp to payload
        payload.timestamp = getTimestampMillis();

        // create byte array to output data to radio
        uint8_t radioBuffer[sizeof payload];

        // convert payload to byte array for transmission
        toByteArray<Test_Payload>(radioBuffer, payload);

        // transmit byte array containing payload data
        downlink::transmit(radioBuffer, sizeof radioBuffer);

        Serial.println("Transmitting payload: " + payload.toLineProtocol());
    }
}