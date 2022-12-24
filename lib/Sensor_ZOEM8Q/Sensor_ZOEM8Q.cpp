//
// Created by robos on 23/12/2022.
//

#include "Sensor_ZOEM8Q.h"

int8_t Sensor_ZOEM8Q::setup() {
    log("Startup...");
    _pipe->begin();
    _pipe->setClock(_freq);

    if (!gnss->begin(*_pipe)) { // deviceAddress = 0x42, maxWait = defaultMaxWait, assumeSuccess = false
        log("GNSS not detected at default I2C address. Please check wiring.");
        return (int8_t) 1; // failure;
    }

    log("Configuring navigation frequency");
    gnss->setNavigationFrequency(5);

    log("Entering autoPVT mode");
    gnss->setAutoPVT(true); // Tell the GNSS to "send" each solution
    log("Setup complete");
    return 0; // success
}

int8_t Sensor_ZOEM8Q::loop() {
    if (gnss->getPVT() &&  !gnss->getInvalidLlh() ) {

        auto *gnss_msg = new GNSSDataMsg(GNSSDataMsg_t);
        gnss_msg->latitude = (float) (gnss->getLatitude() * (10e-8)); // degrees
        gnss_msg->longitude = (float) (gnss->getLongitude() * (10e-8)); // degrees

        // this is the height above the WGS84 ellipsoid, not mean sea level - which is best?
        gnss_msg->altitude = (float) (gnss->getAltitudeMSL() * (10e-4)); // metres

        gnss_msg->fixType = gnss->getFixType();
        gnss_msg->SIV = gnss->getSIV();

        publish(gnss_msg);
    }

    return 0; // success
}