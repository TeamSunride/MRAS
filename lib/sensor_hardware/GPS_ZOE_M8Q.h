//
// Created by Tom Danvers on 19/06/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_GPS_ZOE_M8Q_H
#define MRASV2_GPS_ZOE_M8Q_H


#include "SparkFun_u-blox_GNSS_Arduino_Library.h"
#include "GPS.h"

#define NAVIGATION_FREQUENCY 5

class GPS_ZOE_M8Q : public GPS {
public:
    int8_t begin() override;
    int8_t readData() override;
private:
    SFE_UBLOX_GNSS GNSS;
};


#endif //MRASV2_GPS_ZOE_M8Q_H
