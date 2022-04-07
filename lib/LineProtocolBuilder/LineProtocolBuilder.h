//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_LINEPROTOCOLBUILDER_H
#define MRASV2_LINEPROTOCOLBUILDER_H

#include "Arduino.h"
#include "Time.h"

// https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/

/*
 * Class to help with construction of Line Protocol strings
 */
class LineProtocolBuilder {
public:
    explicit LineProtocolBuilder(const String& measurementName);
    LineProtocolBuilder addTag(const String& tagKey, const String& tagValue);
    LineProtocolBuilder addField(const String& fieldKey, const String& fieldValue);
    LineProtocolBuilder setTimestamp(const unsigned long &timestamp);

    String build();
private:
    String _line;
    String _measurement_name;
    String _tag_set;
    String _field_set;

    unsigned long _timestamp = 0;

    int8_t _number_of_fields = 0;


};


#endif //MRASV2_LINEPROTOCOLBUILDER_H
