//
// Created by Nikilesh -- 8/3/2023
//

#include "MRAS_Config.h"
#include "MRAS_System.h"
#include "ArduinoTextLogger.h"
#include "NativeDataLogger.h"
#include "Arduino.h"
#include "ArduinoBuzzer.h"
#include "StateEstimator.h"
#include "SimulinkDataLogger.h"

auto logger = ArduinoTextLogger(0, 0);
MRAS_System *mras = MRAS_System::get_instance();

NativeDataLogger data_logger = NativeDataLogger(1);


StateEstimator altitudeEstimator = StateEstimator(8, 0.05);


SimulinkDataLogger sim_logger = SimulinkDataLogger(10,3,9600);

ArduinoBuzzer buzzer = ArduinoBuzzer(11, 10);


void setup() {
    mras->set_logger(&logger);
    mras->set_buzzer(&buzzer);

    mras->add_subsystem(&data_logger);
    mras->add_subsystem(&sim_logger);
    mras->add_subsystem(&altitudeEstimator);

    altitudeEstimator.add_subscriber(&sim_logger);
    sim_logger.add_subscriber(&altitudeEstimator);

    mras->setup();
}

void loop() {
    mras->loop();
    delay(0);

}