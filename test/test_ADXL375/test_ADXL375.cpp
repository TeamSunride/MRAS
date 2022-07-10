//
// Created by Tom Danvers on 10/07/2022.
// 2022 TeamSunride.
//

#include "unity.h"
#include "Arduino.h"
#include "Accelerometer_ADXL375.h"
#include "Int64String.h" // pio being really weird again

Accelerometer_ADXL375 adxl = Accelerometer_ADXL375(0x53, &Wire2);

void test_adxl375_begin() {
    TEST_ASSERT_EQUAL(0, adxl.begin());
}

void test_adxl375_acceleration() {
    adxl.readData();
    Vector3D accelVector = adxl.getAcceleration();

    Serial.println("Accel vector: ");
    Serial.println("X: " + String(accelVector.getX()));
    Serial.println("Y: " + String(accelVector.getY()));
    Serial.println("Z: " + String(accelVector.getZ()));

    double magnitude = sqrt(
            pow(accelVector.getX(), 2) + pow(accelVector.getY(), 2) + pow(accelVector.getZ(), 2)
    );

    Serial.println("Accel magnitude: " + String(magnitude) + " m/s^-2");

    TEST_ASSERT_FLOAT_WITHIN(1.5, 9.81, magnitude);
}

void setup() {
    UNITY_BEGIN();

    Wire2.begin();

    RUN_TEST(test_adxl375_begin);

    delay(50);

    RUN_TEST(test_adxl375_acceleration);

    UNITY_END();
}

void loop() {}