#include <unity.h>
#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include "timestamp.h"
#include "Int64String.h"

SFE_UBLOX_GNSS myGNSS;

void test_gps_setup(){
    TEST_ASSERT_TRUE(myGNSS.begin());

    TEST_ASSERT_TRUE(myGNSS.setI2COutput(COM_TYPE_UBX | COM_TYPE_NMEA)); //Set the I2C port to output both NMEA and UBX messages
    TEST_ASSERT_TRUE(myGNSS.saveConfigSelective(VAL_CFG_SUBSEC_IOPORT)); //Save (only) the communications port settings to flash and BBR
}

void test_gps_rtc() {

    uint32_t us;  //microseconds returned by getUnixEpoch()
    uint32_t epoch = myGNSS.getUnixEpoch(us);

    uint64_t teensyRTCUnixMillis = getTimestampMillis();

    uint64_t gpsUnixMillis = ((uint64_t) epoch * 1000000 + us)/1000;
    Serial.print("GPS Unix Time (ms):    "); Serial.println(int64String(gpsUnixMillis));
    Serial.print("Teensy Unix Time (ms): "); Serial.println(int64String(teensyRTCUnixMillis));

    uint64_t delta = abs(gpsUnixMillis - teensyRTCUnixMillis);
    TEST_ASSERT_INT16_WITHIN(2000, 0, delta); // the two time readings must be within 1 second of each other to pass
}

void setup() {
    UNITY_BEGIN();

    Wire.begin();

    RUN_TEST(test_gps_setup);
    RUN_TEST(test_gps_rtc);

    UNITY_END();
}

void loop() {
}