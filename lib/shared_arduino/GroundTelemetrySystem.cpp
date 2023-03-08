//
// Created by Tom Danvers on 06/02/2023.
//

#include "GroundTelemetrySystem.h"

int8_t GroundTelemetrySystem::loop() {
    Module *mod = radio.getMod();
    if (telemetry_system_state != IDLE) {
        // check interrupt pin of radio and return if the radio is busy
        if (!mod->digitalRead(mod->getIrq())) {
            return 0;
        }

        radio.finishTransmit();
    }

//    log("[SX1280] Ranging ... ");

    // start ranging exchange
    // range as master:             true
    // slave address:               0x12345678
//    int state = radio.range(true, 0x12122121);

    // the other module must be configured as slave with the same address
    /*
      int state = radio.range(false, 0x12345678);
    */
//
//    // if ranging calibration is known, it can be provided
//    // this should improve the accuracy and precision
//    uint16_t calibration[3][6] = {
//            { 10299, 10271, 10244, 10242, 10230, 10246 },
//            { 11486, 11474, 11453, 11426, 11417, 11401 },
//            { 13308, 13493, 13528, 13515, 13430, 13376 }
//    };
//
//    int state = radio.range(rangingMasterOrSlave, 0x12345678, calibration);
//
//    if (state == RADIOLIB_ERR_NONE) {
//        // ranging finished successfully
//        float distance = radio.getRangingResult();
//        log("Success! [SX1280] Distance:\t\t\t %f meters (raw)", distance);
//        rangingMasterOrSlave = !rangingMasterOrSlave;
////        Serial.println(F("success!"))
////        Serial.print(F("[SX1280] Distance:\t\t\t"));
////        Serial.print(radio.getRangingResult());
////        Serial.println(F(" meters (raw)"));
//
//    } else if (state == RADIOLIB_ERR_RANGING_TIMEOUT) {
//        // timed out waiting for ranging packet
//        log("timed out!");
//
//    } else {
//        // some other error occurred
//        log("failed, code %d", state);
//
//    }
//    delay(1000);



    switch (telemetry_system_state) {
        case IDLE: {
            // ground station starts by receiving the next message
            start_receiving_next_message();
            log("SNR: %f    RSSI: %f", radio.getSNR(), radio.getRSSI());
            break;
        }
        case TX: {
            transmit_next_message();
            log("SNR: %f    RSSI: %f", radio.getSNR(), radio.getRSSI());
            break;
        }
        case RX: {
            auto* msg = new ReceivedTelemetryMessageMsg();
            log("SNR: %f    RSSI: %f", radio.getSNR(), radio.getRSSI());
            if (read_new_message_from_buffer(msg)) {
                publish(msg);
            } else {
                log("CRC or radio error");
                delete msg;
            }
        }
    }
    return 0;
}
