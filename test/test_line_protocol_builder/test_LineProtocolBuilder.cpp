//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#include "LineProtocolBuilder.h"
#include "unity.h"

void print_strings(const String& target, const String& line) {
    Serial.println("Target: ");
    Serial.println(target);

    Serial.println("Line: ");
    Serial.println(line);
}

void test_string_types() {
    String target = R"(testing,myTag="myTagValue",anotherTag="anotherTagValue" myField="myFieldValue",anotherField="anotherFieldValue" 9223372036854775806)";
    String line = LineProtocolBuilder("testing")
            .addTag("myTag", "myTagValue")
            .addTag("anotherTag", "anotherTagValue")
            .addField("myField", "myFieldValue")
            .addField("anotherField", "anotherFieldValue")
            .setTimestamp(9223372036854775806ULL).build();

    print_strings(target, line);

    TEST_ASSERT_TRUE(line == target)
}

void test_float_types() {
    String target = R"(testing,myTag=5.4210 myField=123.1513 1234)";
    String line = LineProtocolBuilder("testing")
            .addTag("myTag", 5.421f)
            .addField("myField", 123.1513f)
            .setTimestamp(1234).build();

    print_strings(target, line);

    TEST_ASSERT_TRUE(line == target)
}

void test_int64_t() {
    // LL needed for the compiler to parse the numbers correctly
    int64_t MIN_INT64 = -9223372036854775807LL;
    int64_t MAX_INT64 = 9223372036854775807LL;

    String target = R"(testing,myTag=-9223372036854775807i myField=9223372036854775807i 1234)";
    String line = LineProtocolBuilder("testing")
            .addTag("myTag", MIN_INT64)
            .addField("myField", MAX_INT64)
            .setTimestamp(1234).build();

    print_strings(target, line);

    TEST_ASSERT_TRUE(line == target)
}

void test_uint64_t() {
    // ULL needed for the compiler to parse the numbers correctly
    uint64_t MAX_UINT64 = 18446744073709551615ULL;
    uint64_t UINT64 = 4527492349271ULL;

    String target = R"(testing,myTag=18446744073709551615u myField=4527492349271u 1234)";
    String line = LineProtocolBuilder("testing")
            .addTag("myTag", MAX_UINT64)
            .addField("myField", UINT64)
            .setTimestamp(1234).build();

    print_strings(target, line);

    TEST_ASSERT_TRUE(line == target)
}


void test_boolean() {
    String target = R"(testing,myTag=t myField=f 1234)";
    String line = LineProtocolBuilder("testing")
            .addTag("myTag", true)
            .addField("myField", false)
            .setTimestamp(1234).build();

    print_strings(target, line);

    TEST_ASSERT_TRUE(line == target)
}

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_string_types);
    RUN_TEST(test_float_types);
    RUN_TEST(test_int64_t);
    RUN_TEST(test_uint64_t);
    RUN_TEST(test_boolean);

    UNITY_END();
}

void loop() {
}