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
#include "payloads/DARTDebugPayload.h"

#define SPI0_FREQUENCY  4000000

// define sensors (specific hardware)
Barometer_MS5607 ms5607 = Barometer_MS5607(0x76, &Wire2);
//IMU_MPU6050 mpu6050 = IMU_MPU6050();
GPS_ZOE_M8Q zoe_m8q = GPS_ZOE_M8Q();
// Accelerometer_ADXL375 adxl375 = Accelerometer_ADXL375(&Wire2, 0x53);
Accelerometer_ADXL375 adxl375 = Accelerometer_ADXL375(3, SPI, SPI0_FREQUENCY);
LSM6DSO32 LSM(40, SPI, SPI0_FREQUENCY);
LIS3MDL LIS(37, SPI, SPI0_FREQUENCY);
IMU_LSM_LIS imu_lsm_lis = IMU_LSM_LIS(&LSM, &LIS);

// define sensors (interfaces)
Barometer *barometer = &ms5607;
IMU *imu = &imu_lsm_lis;
GPS *gps = &zoe_m8q;
Accelerometer *accelerometer = &adxl375;

Sensor *sensors[] = { barometer, imu, gps, accelerometer };

int packets_sent = 0;
int packets_logged = 0;
uint32_t last_packet_update = 0;

// file for SD card logging
File log_file;

void setup() {
    // set the Time library to use Teensy's RTC to keep time
    setSyncProvider(getTeensy3Time);

    Serial.begin(2000000);

    Serial.println("Welcome to MRAS");
    buzzer_startup();

    // begin I2C bus
    Wire.begin();
    Wire2.begin();

    downlink::setupRadio();

    // tell the radio to operate in explicit header mode for variable payload types
    downlink::radio.explicitHeader();

    // init all sensors
    int i = 0;
    for (Sensor *sensor: sensors) {
        int8_t result = sensor->begin();
        if (result == 0) {
            int frequency = 1500 + i * 100;
            buzzer_tone(frequency, 100, true);
            delay(20);
            buzzer_tone(frequency, 100, true);
        } else {
            buzzer_tone(600, 5000, true);
        }

        delay(100);
        i++;
    }

    // setup SD card
    if (!SD.begin(BUILTIN_SDCARD)) {
        Serial.println("SD card init failed");
        buzzer_error();
    }

    char filename[8] = "";
    // pick an appropriate file name
    for (int i = 0; i < 1000; i++) {
        sprintf(filename, "%d.csv", i);
        if (!SD.exists(filename)) {
            break;
        }
    }

    Serial.print("SD filename: ");
    Serial.println(filename);

    log_file = SD.open(filename, FILE_WRITE);
}

void loop() {
    // Read data from sensors
    uint32_t DAQStart = millis();
    for (Sensor *sensor: sensors) {
        sensor->readData();
    }
    delay(2);
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

    // construct payload object for transmission
    DARTDebugPayload payload(imu, gps, barometer, accelerometer);
    // add timestamp to payload
    payload.timestamp = getTimestampMillis();
    payload.DAQTime = DAQTime > 255 ? 255 : DAQTime;


    char output_string[512];
    payload.toLineProtocol(output_string);

    log_file.println(output_string);
    packets_logged++;

    if (downlink::radioAvailable) {

        // create byte array to output data to radio
        uint8_t radioBuffer[sizeof payload];

        // convert payload to byte array for transmission
        toByteArray<DARTDebugPayload>(radioBuffer, payload);

        // transmit byte array containing payload data
        downlink::transmit(radioBuffer, sizeof radioBuffer);

        //Serial.println(output_string);

        packets_sent++;
    }

    if (millis() - last_packet_update > 1000) {
        Serial.printf("Packets sent: %d Logged: %d\n", packets_sent, packets_logged);

        // make sure bytes are written to SD card
        log_file.flush();

        if (MRAS_ENABLE_BEEPING) {
            if (packets_sent > 0) {
                buzzer_tone(1000 + packets_sent * 20, 50);
            } else {
                buzzer_tone(500, 100);
            }
        }

        packets_sent = 0;
        packets_logged = 0;
        last_packet_update = millis();
    }
}