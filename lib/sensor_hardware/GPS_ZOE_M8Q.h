//
// Created by Tom Danvers on 19/06/2022.
// 2022 TeamSunride.
//

#ifndef MRAS_GPS_ZOE_M8Q_H
#define MRAS_GPS_ZOE_M8Q_H


#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include "GPS.h"
#include <TimeLib.h>


#define NAVIGATION_FREQUENCY 5

class GPS_ZOE_M8Q : public GPS {
public:
    int8_t begin() override;
    int8_t readData() override;

    void performOnlineAssist();
private:
    SFE_UBLOX_GNSS GNSS;
};


#endif //MRAS_GPS_ZOE_M8Q_H
