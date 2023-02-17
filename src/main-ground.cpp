//
// Created by Tom Danvers on 05/12/2022.
//

#include "Arduino.h"
#include "ArduinoTextLogger.h"
#include "MRAS_System.h"
#include "NativeDataLogger.h"
#include "GroundTelemetrySystem.h"
#include "GroundSDLogger.h"

#define LAMBDA_CS_PIN 0

auto logger = ArduinoTextLogger(0, 2000000);
MRAS_System *mras = MRAS_System::get_instance();

GroundTelemetrySystem telemetry_system = GroundTelemetrySystem(7);
NativeDataLogger data_logger = NativeDataLogger(1);
GroundSDLogger sd_logger = GroundSDLogger(8, 4);

void setup() {
    while (!Serial) {}


    pinMode(LAMBDA_CS_PIN, OUTPUT); // Set the CS pin of the RADIO system HIGH (to disable it) before trying to initialise SD card
    digitalWrite(LAMBDA_CS_PIN, HIGH); // Otherwise there's interference on the SPI bus,

    mras->set_logger(&logger);
//    mras->add_subsystem(&sd_logger);
    mras->add_subsystem(&telemetry_system);
//    mras->add_subsystem(&data_logger);

//    telemetry_system.add_subscriber(&data_logger);
//    telemetry_system.add_subscriber(&sd_logger);

//    logger.add_subscriber(&sd_logger);

    mras->setup();
}

void loop() {
    mras->loop();
//    delay(100);
    //Serial.println(millis());
}