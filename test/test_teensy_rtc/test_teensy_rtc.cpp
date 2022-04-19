#include <teensy_rtc.h>
#include <unity.h>

uint32_t previousMillis = 0;
uint32_t interval = 1;

uint32_t testLength = 30000;
uint32_t testStart = 0;

void setup() {
  delay(2000);
  Serial.begin(115200);
  while(!Serial);
  UNITY_BEGIN();
  testStart = millis();
}

void loop() {
  uint32_t currentMillis = millis();
  if(currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    uint64_t currentTime = getTime();
    Serial.println(currentTime);
  }
  uint32_t currentMillis2 = millis();
  if(currentMillis2 - testStart >= testLength) {
    UNITY_END();
  }
}