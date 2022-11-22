//
// Created by Tom Danvers on 19/06/2022.
// 2022 TeamSunride.
//

#include "GPS_ZOE_M8Q.h"
#include "SD.h"

int8_t GPS_ZOE_M8Q::begin() {
    int8_t returnStatusCode = 0;

#ifdef DART_PINS
    TwoWire* port = &Wire;
#elif MRAS_DART_PINS
    TwoWire* port = &Wire2;
#endif

    Serial.println("Setting up ZOE-M8Q");

    if (GNSS.begin(*port, 0x42, 1100, false)) {
        Serial.println("GPS begin() success");
    }else {
        Serial.println("GPS begin() failure");
        return -1;
    }

    // Set the I2C port to output UBX only (turn off NMEA noise)
    if (!GNSS.setI2COutput(COM_TYPE_UBX)) returnStatusCode = -2;

    if (!GNSS.setNavigationFrequency(NAVIGATION_FREQUENCY)) returnStatusCode = -3;

    // Tell the GNSS to "send" each solution
    if (!GNSS.setAutoPVT(true)) returnStatusCode = -4;

    // Save the current settings to flash and BBR
    if (!GNSS.saveConfiguration()) returnStatusCode = -5;

    // set the GPS dynamic model to DYN_MODEL_AIRBORNE4g (untested)
    if (!GNSS.setDynamicModel(DYN_MODEL_AIRBORNE4g)) returnStatusCode = -6;

    //performOnlineAssist();

    if (returnStatusCode != 0) {
        Serial.println("GPS setup failed. Status code: " + String(returnStatusCode));
    } else {
        Serial.println("GPS setup success");
    }

    return returnStatusCode;
}

int8_t GPS_ZOE_M8Q::readData() {
    // Calling getPVT returns true if there actually is a fresh navigation solution available.
    // Start the reading only when valid LLH is available
    if (GNSS.getPVT() && !GNSS.getInvalidLlh()) {
        // convert lat and long to degrees
        _latitude = (float) (GNSS.getLatitude() / 1e7);
        _longitude = (float) (GNSS.getLongitude() / 1e7);
        _altitude = (float) (GNSS.getAltitudeMSL() / 1e3);
        _satellites_in_view = GNSS.getSIV();
        _fix_type = GNSS.getFixType();
    }

    return 0;
}

// From Daedalus code
uint64_t getTimestampMillisGPS() // syncs the RTC on tje teensy 4.1 with the unix time at compile time
{
    // Created by Ashley Shaw on 19/04/2022 using stuff from https://forum.pjrc.com/threads/68062-Teensy-4-1-RTC-get-milliseconds-correctly
    // 2022 TeamSunride.
    //

    uint64_t periods;
    uint32_t hi1 = SNVS_HPRTCMR, lo1 = SNVS_HPRTCLR;
    while (true)
    {
        uint32_t hi2 = SNVS_HPRTCMR, lo2 = SNVS_HPRTCLR;
        if (lo1 == lo2 && hi1 == hi2)
        {
            periods = (uint64_t)hi2 << 32 | lo2;
            break;
        }
        hi1 = hi2;
        lo1 = lo2;
    }
    uint32_t ms = (1000 * (periods % 32768)) / 32768;
    time_t sec = periods / 32768;
    tm t = *gmtime(&sec);

    setTime(t.tm_hour-1, t.tm_min, t.tm_sec, t.tm_mday, t.tm_mon + 1, t.tm_year + 1900);

    uint64_t unixTime = (uint64_t(now()) * 1000) + ms;
    return unixTime;
}

unsigned short GPSweek() {
    // 315964800 is the unix timestamp (s) of midnight 6th Jan 1980 - the start of GPS time
    // There has been 18 leap seconds since this date (unix time does not account for leap seconds)
    // not sure when the next leap second is due
    u_int64_t diff = (getTimestampMillisGPS()/1000) - 315964800 + 18;
    return (unsigned short) (diff / SECS_PER_WEEK);
}

unsigned int actualTimeOfWeekms() {
    // The time of week is the number of seconds since Sunday midnight (00:00:00)

    // 315964800000 is the unix timestamp (ms) of 6th Jan 1980 - the start of GPS time |
    // There has been 18 leap seconds since this date (unix time does not account for leap seconds)
    // not sure when the next leap second is due
    u_int64_t diff = (getTimestampMillisGPS()) - 315964800000 + 18000;
    return (unsigned int) ((diff) % (SECS_PER_WEEK*1000));
}

void GPS_ZOE_M8Q::performOnlineAssist() {
    /** --------- AIDING SEQUENCE--------- Datasheet section 13.5 (pg. 34)
     *   --- Note that we are altering the AID_INI part of the message and leaving the rest as is. ---
     • Power-up the GPS receiver
     • Send UBX-AID-INI (time, clock and position) message.
     • Send UBX-AID-EPH (ephemeris) message.
     • Apply optional hardware time synchronization pulse within 0.5 s after (or before, depending on the
       configuration in UBX-AID-INI) sending the UBX-AID-INI message if hardware time synchronization is
       required. When sending the message before applying the pulse, make sure to allow the GPS receiver to
       parse and process the aiding message. The time for parsing depends on the baud rate. The processing time
       is 100 ms maximum.
     • Send optional UBX-AID-HUI (health, UTC and ionosphere parameters) message.
     • Send optional UBX-AID-ALM (almanac) message. **/

    if (!SD.begin(BUILTIN_SDCARD)) {
        bool sdCardInitialised = false;
        for (int i=0;i<10;i++) {
            if (!SD.begin(BUILTIN_SDCARD)) {
                Serial.println("SD Card failed to initialize");
                delay(500);
            } else {
                Serial.println("SD Card initialized");
                sdCardInitialised = true;
                break;
            }
            delay(1000);
        }
        if (!sdCardInitialised) {
            Serial.println("Could not mount SD card");
            while(1);
        }

    }
    Serial.println("Card initialised");

    /// this file ("mgaonline.ubx") should be loaded into the onboard SD card
    /// the file should be obtained from the ublocks server
    /// the generator token for that can be obtained from thingstream from ublocks
    /// See https://developer.thingstream.io/guides/location-services/assistnow-getting-started-guide for more details
    File dataFile = SD.open("mgaonline.ubx");
    const int numbytes = dataFile.available();
    Serial.printf("File size: %d\n", numbytes);
    if (!dataFile) {
        Serial.println("Failed to open file");
        while (true);
    }
    byte * fileBuffer = new byte[numbytes]; // use new for array of variable size - remember to delete[] !
    dataFile.readBytes(reinterpret_cast<char *>(fileBuffer), numbytes);

    Serial.printf("%d:%d:%d,  %d/%d/%d", hour(), minute(), second(), day(), month(), year());
    Serial.printf("GPS WEEK: %d\n", GPSweek());
    Serial.printf("GPS time of week: %d\n", actualTimeOfWeekms());

    // alter the necessary fields in the file buffer AID_INI

    // configure week number, little endian /:)
    int headerLength = 6;
    unsigned short gpsweek = GPSweek();
    fileBuffer[18+headerLength] = (gpsweek & 0x00FF);
    fileBuffer[19+headerLength] = (gpsweek & 0xFF00) >> 8;

    // configure time of week, little endian /:)
    unsigned long timeOfWeekms = actualTimeOfWeekms()+150;
    fileBuffer[20+headerLength] = (timeOfWeekms & 0x000000FF);
    fileBuffer[21+headerLength] = (timeOfWeekms & 0x0000FF00) >> 8;
    fileBuffer[22+headerLength] = (timeOfWeekms & 0x00FF0000) >> 16;
    fileBuffer[23+headerLength] = (timeOfWeekms & 0xFF000000) >> 24;

    Serial.println("\n\n\n");

    // setting the new checksums
    uint8_t CK_A = 0;
    uint8_t CK_B = 0;

    for (int i=2;i<54;i++) {
        CK_A += fileBuffer[i];
        CK_B += CK_A;
    }
    fileBuffer[54] = CK_A;
    fileBuffer[55] = CK_B;
    Serial.printf("CK_A: %02X      CK_B: %02X", CK_A, CK_B);

    for (int i=0;i<56;i++) {
        Serial.printf("%02X ",fileBuffer[i]);
    }
    Serial.println("HERE1");
    GNSS.setAckAiding(1);
    GNSS.setI2CpollingWait(1);
    GNSS.enableDebugging(Serial, true);
    GNSS.pushAssistNowData(fileBuffer, (size_t)fileBuffer, SFE_UBLOX_MGA_ASSIST_ACK_ENQUIRE, 100);
    GNSS.setI2CpollingWait(2);
    Serial.println("HERE2");

//    Serial.printf("\nAvailable for write: %d\n", gpsSerial.availableForWrite());
//    for (int  i=0;i<numbytes; i++) {
//        gpsSerial.write(fileBuffer[i]);
//        gpsSerial.flush(); // flush waits for the above write to finish
//
//    }

    dataFile.close();
    delete[] fileBuffer; // delete[] - very important - we don't like them segfaults

    Serial.println("\nFinished performOnlineAssist()\n");

}