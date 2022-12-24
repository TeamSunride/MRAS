//
// Created by robos on 17/12/2022.
//

#ifndef MRAS_ARDUINOTEXTLOGGER_H
#define MRAS_ARDUINOTEXTLOGGER_H

#include "Arduino.h"
#include "TextLogger.h"
#include "HIL_messages.pb.h"
#include <pb_encode.h>
#include <pb_decode.h>
#include <cstdio>
#include <cstdarg>

#define PROTOBUF_TEXTLOG

class ArduinoTextLogger : public TextLogger {
private:
    long _baud;
public:
    explicit ArduinoTextLogger(uint8_t id, long baud) : TextLogger(id) {
        _baud = baud;
    };

    void _log(const char *fmt, va_list args) override;

    int8_t setup() override {
        Serial.begin(_baud);
        log("Successfully set up Serial connection");
        return 0;
    }

    int8_t loop() override {
        return 0;
    }

    SUBSYSTEM_NAME("ArduinoTextLogger")
};

void ArduinoTextLogger::_log(const char *fmt, va_list args) {
    // https://stackoverflow.com/questions/20639632/how-to-wrap-printf-into-a-function-or-macro
    char string[255] = {};
    vsprintf(string, fmt, args);
#ifdef PROTOBUF_TEXTLOG
    uint8_t protobuf_outbuffer[300];
    ProtobufTextLogMsg msg = ProtobufTextLogMsg_init_zero;
    strcpy(msg.text, string);
    pb_ostream_t stream = pb_ostream_from_buffer(protobuf_outbuffer, sizeof(protobuf_outbuffer));
    pb_encode(&stream, ProtobufTextLogMsg_fields, &msg);
    uint16_t bytes_written = stream.bytes_written;
    Serial.write(reinterpret_cast<uint8_t*>(&bytes_written), sizeof(bytes_written));
    Serial.write(protobuf_outbuffer, stream.bytes_written);
    Serial.write('\r');
#else
    Serial.print(string);
#endif
}

#endif //MRAS_ARDUINOTEXTLOGGER_H
