//
// Created by Tom Danvers on 15/03/2022.
// 2022 TeamSunride.
//

#include "Arduino.h"
#include "Barometer.h"
#include "Barometer_MS5607.h"
#include "SimpleKalmanFilter.h"

// define sensors
Barometer *barometer = new Barometer_MS5607();
Sensor *sensors[] = {barometer};

// define filters
SimpleKalmanFilter pressureFilter = SimpleKalmanFilter(1, 1, 1);

void setup() {
    Serial.begin(9600);
    barometer->begin();
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
    Serial.println("pressureTest "
                   "measuredPressure=" + String(measured_pressure) + ","
                   "filteredPressure=" + String(filtered_pressure) + ","
                   "daqTime=" + String(data_acq_time));
}