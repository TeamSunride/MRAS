//
// Created by robos on 23/12/2022.
//

#include "Sensor_ZOEM8Q.h"

int8_t Sensor_ZOEM8Q::setup() {
    _pipe->begin();
    _pipe->setClock(_freq);

    if (!gnss->begin(*_pipe)) { // deviceAddress = 0x42, maxWait = defaultMaxWait, assumeSuccess = false
        log("GNSS not detected at default I2C address. Please check wiring.");
        return (int8_t) 1; // failure;
    }

    gnss->setNavigationFrequency(5);
    gnss->setAutoPVT(true); // Tell the GNSS to "send" each solution

    // perform the online assist process - uses mgaonline.ubx file from SD card
    performOnlineAssist();
    log("GNSS setup finished");
    return 0; // success
}

int8_t Sensor_ZOEM8Q::loop() {
    if (gnss->getPVT() &&  !gnss->getInvalidLlh() ) {

        auto *gnss_msg = new GNSSDataMsg(GNSSDataMsg_t);
        gnss_msg->latitude = (float) (gnss->getLatitude() * (10e-8)); // degrees
        gnss_msg->longitude = (float) (gnss->getLongitude() * (10e-8)); // degrees

        // The altitude above mean sea level - NOT the altitude above the WGS84 ellipsoid
        gnss_msg->altitude = (float) (gnss->getAltitudeMSL() * (10e-4)); // metres

        gnss_msg->fix_type = gnss->getFixType(); /// 1: no fix, 2: 2D fix, 3: 3D fix 4: GNSS + dead reckoning combined, 5: time only fix
        gnss_msg->SIV = gnss->getSIV();

        log("Time From GPS: %d:%d:%d,  %d/%d/%d", gnss->getHour(), gnss->getMinute(), gnss->getSecond(), gnss->getDay(), gnss->getMonth(), gnss->getYear());

        publish(gnss_msg);
    }

    return 0; // success
}





// From Daedalus code

uint64_t getTimestampMillisGPS() {/// syncs the RTC on tje teensy 4.1 with the unix time at compile time
    // Created by Ashley Shaw on 19/04/2022 using stuff from https://forum.pjrc.com/threads/68062-Teensy-4-1-RTC-get-milliseconds-correctly
    // 2022 TeamSunride.
    //
    uint64_t periods;
    uint32_t hi1 = SNVS_HPRTCMR, lo1 = SNVS_HPRTCLR;
    while (true) {
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

    // the first parameter needs decremented by one if Daylight saving is in effect (from last sunday in March to last sunday in October - https://www.gov.uk/when-do-the-clocks-change
    setTime(t.tm_hour, t.tm_min, t.tm_sec, t.tm_mday, t.tm_mon + 1, t.tm_year + 1900);

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

int8_t Sensor_ZOEM8Q::performOnlineAssist() {
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
        for (int i=0;i<3;i++) {
            if (!SD.begin(BUILTIN_SDCARD)) {
                log("SD Card failed to initialize");
            } else {
                log("SD Card initialized");
                sdCardInitialised = true;
                break;
            }
            delay(1000);
        }
        if (!sdCardInitialised) {
            log("Could not mount SD card");
            return -1;
        }
    }
    log("Card initialised");

    /// this file ("mgaonline.ubx") should be loaded into the onboard SD card
    /// the file should be obtained from the ublocks server
    /// the generator token for that can be obtained from thingstream from ublocks
    /// See https://developer.thingstream.io/guides/location-services/assistnow-getting-started-guide for more details
    File dataFile = SD.open("mgaonline.ubx");

    const int numbytes = dataFile.available();

    log("File size: %d\n", numbytes);

    if (!dataFile) {
        dataFile.close();
        log("Failed to open file");
        return -1;
    }
    byte * fileBuffer = new byte[numbytes]; // use new for array of variable size - remember to delete[] !
    dataFile.readBytes(reinterpret_cast<char *>(fileBuffer), numbytes);


    log("Unix time: %llu", (long long unsigned int) getTimestampMillisGPS());
    log("Time: %d:%d:%d,  %d/%d/%d", hour(), minute(), second(), day(), month(), year());
    log("GPS WEEK: %d\n", GPSweek());
    log("GPS time of week: %d\n", actualTimeOfWeekms());



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

    // setting the new checksums
    uint8_t CK_A = 0;
    uint8_t CK_B = 0;
    for (int i=2;i<54;i++) {
        CK_A += fileBuffer[i];
        CK_B += CK_A;
    }

    fileBuffer[54] = CK_A;
    fileBuffer[55] = CK_B;
    log("CK_A: %02X      CK_B: %02X", CK_A, CK_B);

    // Commenting out Sam's spam
//    for (int i=0;i<56;i++) {
//        log("%02X ",fileBuffer[i]);
//    }

    delay(1000);


    gnss->pushRawData(fileBuffer, numbytes);



// How we did it over serial on Daedalus
//    log("\nAvailable for write: %d\n", gpsSerial.availableForWrite());
//    for (int  i=0;i<numbytes; i++) {
//        gpsSerial.write(fileBuffer[i]);
//        gpsSerial.flush(); // flush waits for the above write to finish
//
//    }

    dataFile.close();
    delete[] fileBuffer; // delete[] - very important - we don't like them segfaults

    log("Finished performOnlineAssist()\n");
    return 0;
}