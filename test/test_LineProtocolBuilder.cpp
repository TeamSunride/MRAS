//
// Created by Tom Danvers on 07/04/2022.
// 2022 TeamSunride.
//

#include "LineProtocolBuilder.h"
#include "unity.h"

void test_string_types() {
    String target = R"(testing,myTag="myTagValue",anotherTag="anotherTagValue" myField="myFieldValue",anotherField="anotherFieldValue" 1234)";
    String line = LineProtocolBuilder("testing")
            .addTag("myTag", "myTagValue")
            .addTag("anotherTag", "anotherTagValue")
            .addField("myField", "myFieldValue")
            .addField("anotherField", "anotherFieldValue")
            .setTimestamp(1234).build();

    Serial.println("Target: ");
    Serial.println(target);

    Serial.println("Line: ");
    Serial.println(line);

    TEST_ASSERT_TRUE(line == target)
}

void setup() {
    UNITY_BEGIN();

    RUN_TEST(test_string_types);

    UNITY_END();
}

void loop() {
}