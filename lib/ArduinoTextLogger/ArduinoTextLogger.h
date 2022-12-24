//
// Created by robos on 17/12/2022.
//

#ifndef MRAS_ARDUINOTEXTLOGGER_H
#define MRAS_ARDUINOTEXTLOGGER_H

#include "Arduino.h"
#include "TextLogger.h"
#include "MRAS.pb.h"
#include "protobuf_util.h"
#include <pb_encode.h>
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
    MRASProtobufMsg msg = MRASProtobufMsg_init_zero;
    msg.which_message = MRASProtobufMsg_text_log_tag;
    strcpy(msg.message.text_log.text, string);
    send_protobuf_serial(protobuf_outbuffer,
                         sizeof(protobuf_outbuffer),
                         &msg,
                         MRASProtobufMsg_fields);
#else
    Serial.print(string);
#endif
}

#endif //MRAS_ARDUINOTEXTLOGGER_H
