//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#include "LineProtocolBuilder.h"

// https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/

LineProtocolBuilder::LineProtocolBuilder(const String& measurementName) {
    _measurement_name = measurementName;
}

LineProtocolBuilder LineProtocolBuilder::addTag(const String& tagKey, const String& tagValue) {
    _tag_set = _tag_set + ',' + tagKey + '=' + '"' + tagValue + '"';
    return *this;
}

LineProtocolBuilder LineProtocolBuilder::addField(const String &fieldKey, const String &fieldValue) {
    _field_set = _field_set + (_number_of_fields > 0 ? "," : "") + fieldKey + "=" + '"' + fieldValue + '"';
    ++_number_of_fields;
    return *this;
}

LineProtocolBuilder LineProtocolBuilder::setTimestamp(const unsigned long& timestamp) {
    _timestamp = timestamp;
    return *this;
}

String LineProtocolBuilder::build() {
    return _measurement_name + _tag_set + " " + _field_set + " " + (String) _timestamp;
}

