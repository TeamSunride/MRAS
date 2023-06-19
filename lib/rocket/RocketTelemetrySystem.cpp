//
// Created by Tom Danvers on 06/02/2023.
//

#include "RocketTelemetrySystem.h"
#include "telemetry_messages/TelemetryDataMsg.h"
#include "system_messages/GNSSDataMsg.h"
#include "system_messages/AccelerometerDataMsg.h"
#include "system_messages/BarometerDataMsg.h"
#include "system_messages/StateEstimatorMsg.h"

int8_t RocketTelemetrySystem::loop() {
    Module *mod = radio.getMod();
    if (telemetry_system_state != IDLE) {
        // check interrupt pin of radio and return if the radio is busy
        if (!mod->digitalRead(mod->getIrq())) {
            return 0;
        }
    }

    switch (telemetry_system_state) {
        case IDLE: {
            transmit_next_message();
            break;
        }
        case TX: {
            radio.finishTransmit();
            transmit_next_message();
            break;
        }
        case RX: {
            auto *msg = new TelemetryMessageReceivedMsg();
            if (read_new_message_from_buffer(msg)) {
                publish(msg);
            } else {
                log("CRC or radio error");
                delete msg;
            }
            break;
        }
    }
    return 0;
}

/**
 * On the rocket, we send a TelemetryDataMsg by default
 */
TelemetryMessageQueueMsg *RocketTelemetrySystem::get_default_message() {
    auto *message = new KAlphaTelemetryMsg_Packed();
    pack_kalpha_telemetry_msg(&kalpha_msg, message);

    auto *queue_message = new TelemetryMessageQueueMsg();
    queue_message->telemetry_message = message;
    queue_message->size = sizeof(KAlphaTelemetryMsg_Packed);
    return queue_message;
}

void RocketTelemetrySystem::on_message(SystemMessage *msg) {
    switch (msg->get_type()) {
        case GNSSDataMsg_t:
            handle_gnss_data_msg((GNSSDataMsg *) msg);
            break;
        case AccelerometerDataMsg_t:
            kalpha_msg.x_acceleration = ((AccelerometerDataMsg *) msg)->acceleration[0];
            break;
        case BarometerDataMsg_t:
            // limit range of temperatures to 0-255 then cast to uint8_t
            kalpha_msg.temperature = ((BarometerDataMsg *) msg)->temperature;
            break;
        case StateEstimatorMsg_t:
            kalpha_msg.pressure_altitude = ((StateEstimatorMsg *) msg)->estimatedAltitude;

            // determine max altitude
            if (kalpha_msg.max_pressure_altitude < kalpha_msg.pressure_altitude) {
                kalpha_msg.max_pressure_altitude = kalpha_msg.pressure_altitude;
            }
            break;
    }
}

void RocketTelemetrySystem::handle_gnss_data_msg(GNSSDataMsg *msg) {
    gnss_data[msg->id] = *msg;

    // compare the two messages to decide which one to forward to the telemetry message

    // first priority is given to the message with fix = 3
    if (gnss_data[0].fix_type == 3) {
        copy_gnss_data(&gnss_data[0], &kalpha_msg);
        return;
    } else if (gnss_data[1].fix_type == 3) {
        copy_gnss_data(&gnss_data[1], &kalpha_msg);
        return;
    }

    // now check for fix = 2
    if (gnss_data[0].fix_type == 2) {
        copy_gnss_data(&gnss_data[0], &kalpha_msg);
        return;
    } else if (gnss_data[1].fix_type == 2) {
        copy_gnss_data(&gnss_data[1], &kalpha_msg);
        return;
    }

    // now pick the GNSS message with the highest number of satellites
    // GNSS 0 gets priority hence >=
    if (gnss_data[0].SIV >= gnss_data[1].SIV) {
        copy_gnss_data(&gnss_data[0], &kalpha_msg);
        return;
    } else {
        copy_gnss_data(&gnss_data[1], &kalpha_msg);
        return;
    }

    // cover any other case by copying GNSS 0
    copy_gnss_data(&gnss_data[0], &kalpha_msg);
    // don't think this ever happens
}

void RocketTelemetrySystem::copy_gnss_data(GNSSDataMsg *msg, KAlphaTelemetryMsg *dest) {
    dest->latitude = msg->latitude;
    dest->longitude = msg->longitude;
    dest->gnss_altitude = msg->altitude;
    dest->satellites = msg->SIV;
    dest->fix_type = msg->fix_type;
}
