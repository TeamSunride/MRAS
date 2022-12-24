//
// Created by Tom Danvers on 24/12/2022.
//

#include "protobuf_util.h"

void send_protobuf_serial(uint8_t *protobuf_outbuffer, size_t bufsize, const void *src_struct, const pb_msgdesc_s *fields)  {
    pb_ostream_t stream = pb_ostream_from_buffer(protobuf_outbuffer, bufsize);
    pb_encode(&stream, fields, src_struct);
    uint16_t bytes_written = stream.bytes_written;
    Serial.write(reinterpret_cast<uint8_t *>(&bytes_written), sizeof(bytes_written));
    Serial.write(protobuf_outbuffer, stream.bytes_written);
}