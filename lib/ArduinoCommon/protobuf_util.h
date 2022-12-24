//
// Created by Tom Danvers on 24/12/2022.
//

#ifndef MRAS_PROTOBUF_UTIL_H
#define MRAS_PROTOBUF_UTIL_H

#include <pb_encode.h>
#include "Arduino.h"

void send_protobuf_serial(uint8_t *protobuf_outbuffer,
                          size_t bufsize,
                          const void *src_struct,
                          const pb_msgdesc_s *fields);



#endif //MRAS_PROTOBUF_UTIL_H
