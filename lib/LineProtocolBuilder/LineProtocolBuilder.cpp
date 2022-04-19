//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#include "LineProtocolBuilder.h"
#include "Int64String.h"

// https://docs.influxdata.com/influxdb/v2.2/reference/syntax/line-protocol/

LineProtocolBuilder::LineProtocolBuilder(const String& measurementName) {
    _measurement_name = measurementName;
}

LineProtocolBuilder LineProtocolBuilder::setTimestamp(const uint64_t& timestamp) {
    _timestamp = timestamp;
    _timestamp_set = true;
    return *this;
}

String LineProtocolBuilder::build() {
    if (_timestamp_set) {
        return _measurement_name + _tag_set + " " + _field_set + " " + int64String(_timestamp);
    } else {
        return _measurement_name + _tag_set + " " + _field_set;
    }
}

LineProtocolBuilder LineProtocolBuilder::_addTag(const String &tagKey, const String &tagValue) {
    _tag_set = _tag_set + ',' + tagKey + '=' + tagValue;
    return *this;
}

LineProtocolBuilder LineProtocolBuilder::_addField(const String &fieldKey, const String &fieldValue) {
    _field_set = _field_set + (_number_of_fields > 0 ? "," : "") + fieldKey + "=" + fieldValue;
    ++_number_of_fields;
    return *this;
}

LineProtocolBuilder LineProtocolBuilder::addTag(const String& tagKey, const String& tagValue) {
    return _addTag(tagKey, '"' + tagValue + '"');
}

LineProtocolBuilder LineProtocolBuilder::addField(const String &fieldKey, const String &fieldValue) {
    return _addField(fieldKey, '"' + fieldValue + '"');
}

LineProtocolBuilder LineProtocolBuilder::addTag(const String &tagKey, const char * tagValue) {
    return _addTag(tagKey, '"' + String(tagValue) + '"');
}

LineProtocolBuilder LineProtocolBuilder::addField(const String &fieldKey, const char * fieldValue) {
    return _addField(fieldKey, '"' + String(fieldValue) + '"');
}

LineProtocolBuilder LineProtocolBuilder::addTag(const String& tagKey, const float& tagValue) {
    return _addTag(tagKey, String(tagValue, 4));
}

LineProtocolBuilder LineProtocolBuilder::addField(const String &fieldKey, const float &fieldValue) {
    return _addField(fieldKey, String(fieldValue, 4));
}

LineProtocolBuilder LineProtocolBuilder::addTag(const String &tagKey, const int64_t &tagValue) {
    return _addTag(tagKey, int64String(tagValue) + "i");
}

LineProtocolBuilder LineProtocolBuilder::addField(const String &fieldKey, const int64_t &fieldValue) {
    return _addField(fieldKey, int64String(fieldValue) + "i");
}

LineProtocolBuilder LineProtocolBuilder::addTag(const String &tagKey, const uint64_t &tagValue) {
    return _addTag(tagKey, int64String(tagValue) + "u");
}

LineProtocolBuilder LineProtocolBuilder::addField(const String &fieldKey, const uint64_t &fieldValue) {
    return _addField(fieldKey, int64String(fieldValue) + "u");
}

LineProtocolBuilder LineProtocolBuilder::addTag(const String &tagKey, const bool &tagValue) {
    return _addTag(tagKey, tagValue ? 't' : 'f');
}

LineProtocolBuilder LineProtocolBuilder::addField(const String &fieldKey, const bool &fieldValue) {
    return _addField(fieldKey, fieldValue ? 't' : 'f');
}



