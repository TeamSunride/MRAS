//
// Created by Tom Danvers on 05/12/2022.
//

#include "Arduino.h"
#include "ArduinoTextLogger.h"
#include "MRAS_System.h"
#include "NativeDataLogger.h"
#include "GroundTelemetrySystem.h"
#include "GroundSDLogger.h"
#include "ArduinoBuzzer.h"



auto logger = ArduinoTextLogger(0, 2000000);
MRAS_System *mras = MRAS_System::get_instance();

GroundTelemetrySystem telemetry_system = GroundTelemetrySystem(7);
NativeDataLogger data_logger = NativeDataLogger(1);
//GroundSDLogger sd_logger = GroundSDLogger(8, 4);
ArduinoBuzzer buzzer = ArduinoBuzzer(10, A5);

void setup() {
    while (!Serial) {}



    mras->set_logger(&logger);
    mras->set_buzzer(&buzzer);
//    mras->add_subsystem(&sd_logger);
    mras->add_subsystem(&telemetry_system);
    // mras->add_subsystem(&data_logger);

     telemetry_system.add_subscriber(&data_logger);
//    telemetry_system.add_subscriber(&sd_logger);

//    logger.add_subscriber(&sd_logger);

    mras->setup();
}

void loop() {
    mras->loop();
    //Serial.println(millis());
}