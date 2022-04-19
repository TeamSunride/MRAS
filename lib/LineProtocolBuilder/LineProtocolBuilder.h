//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_LINEPROTOCOLBUILDER_H
#define MRASV2_LINEPROTOCOLBUILDER_H

#include "Arduino.h"

// https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/

/*
 * Class to help with construction of Line Protocol strings
 */
class LineProtocolBuilder {
public:
    explicit LineProtocolBuilder(const String& measurementName);

    // String value type
    // https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/#string
    LineProtocolBuilder addTag(const String& tagKey, const String& tagValue);
    LineProtocolBuilder addField(const String& fieldKey, const String& fieldValue);

    // additional overloads for const char* to prevent "wrong" overloaded method with bool
    // https://stackoverflow.com/questions/21161026/c-chooses-wrong-overloaded-method-with-default-parameters
    LineProtocolBuilder addTag(const String& tagKey, const char* tagValue);
    LineProtocolBuilder addField(const String& fieldKey, const char* fieldValue);

    // Float value type
    // https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/#float
    LineProtocolBuilder addTag(const String& tagKey, const float& tagValue);
    LineProtocolBuilder addField(const String& fieldKey, const float& fieldValue);

    // Signed 64-bit integer value type
    // https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/#integer
    LineProtocolBuilder addTag(const String& tagKey, const int64_t& tagValue);
    LineProtocolBuilder addField(const String& fieldKey, const int64_t& fieldValue);

    // Unsigned 64-bit integer value type
    // https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/#uinteger
    LineProtocolBuilder addTag(const String& tagKey, const uint64_t& tagValue);
    LineProtocolBuilder addField(const String& fieldKey, const uint64_t& fieldValue);

    // Boolean value type
    // https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/#boolean
    LineProtocolBuilder addTag(const String& tagKey, const bool& tagValue);
    LineProtocolBuilder addField(const String& fieldKey, const bool& fieldValue);


    LineProtocolBuilder setTimestamp(const uint64_t &timestamp);

    String build();
private:
    String _line;
    String _measurement_name;
    String _tag_set;
    String _field_set;

    LineProtocolBuilder _addTag(const String& tagKey, const String& tagValue);
    LineProtocolBuilder _addField(const String& fieldKey, const String& fieldValue);

    uint64_t _timestamp = 0;
    bool _timestamp_set = false;

    int8_t _number_of_fields = 0;


};


#endif //MRASV2_LINEPROTOCOLBUILDER_H
