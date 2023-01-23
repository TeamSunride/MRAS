//
// Created by Tom Danvers on 16/12/2022.
//

#include <stdio.h>
#include <pb_encode.h>
#include <pb_decode.h>
#include "telemetry.pb.h"
#include "unity.h"

void setUp() {
    // set stuff up here
}

void tearDown() {
    // clean stuff up here
}

int main() {
    UNITY_BEGIN();
    uint8_t buffer[128];
    size_t message_length;
    bool status;
    {


        TelemetryMessage telemetryMessage = TelemetryMessage_init_zero;

        // select which message you want to send (switch statement for ease of testing)
        switch (TelemetryMessage_basicSensorData_tag) {
            case TelemetryMessage_heartbeat_tag: {
                telemetryMessage.message.heartbeat.timestamp = 1;
                telemetryMessage.which_message = TelemetryMessage_heartbeat_tag;
                break;
            }
            case TelemetryMessage_basicSensorData_tag: {
                telemetryMessage.which_message = TelemetryMessage_basicSensorData_tag;
                telemetryMessage.message.basicSensorData = BasicSensorData_init_zero;
                BasicSensorData& data = telemetryMessage.message.basicSensorData;
                data.timestamp = 1671232441013;
                data.pressure = 101325.23;
                data.temperature = 25.6;
                data.latitude = 52.802761;
                data.longitude = -1.552307;
                break;
            }
            case TelemetryMessage_command_tag: {
                telemetryMessage.which_message = TelemetryMessage_command_tag;
                telemetryMessage.message.command.command = Command_WIPE_FLASH_MEMORY;
                break;
            }
        }

        pb_ostream_t stream = pb_ostream_from_buffer(buffer, sizeof(buffer));


        status = pb_encode(&stream, TelemetryMessage_fields, &telemetryMessage);
        message_length = stream.bytes_written;
        printf("Bytes written: %d\n", message_length);

        if (!status) {
            printf("Encoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }
    }



    // transmit message over network

    {
        /* Allocate space for the decoded message. */
        TelemetryMessage telemetryMessage = TelemetryMessage_init_zero;

        /* Create a stream that reads from the buffer. */
        pb_istream_t stream = pb_istream_from_buffer(buffer, message_length);

        /* Now we are ready to decode the message. */
        status = pb_decode(&stream, TelemetryMessage_fields, &telemetryMessage);

        /* Check for errors... */
        if (!status) {
            printf("Decoding failed: %s\n", PB_GET_ERROR(&stream));
            return 1;
        }

        switch (telemetryMessage.which_message) {
            case TelemetryMessage_heartbeat_tag:
                printf("Heartbeat received: timestamp %llu", telemetryMessage.message.heartbeat.timestamp);
                break;
            case TelemetryMessage_basicSensorData_tag:
                printf("Sensor data received");
                break;
            case TelemetryMessage_command_tag:
                printf("Command received");
                break;
        }
    }


    UNITY_END();

    return 0;
}

