//
// Created by Tom Danvers on 05/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_BAROMETER_MS5607_H
#define MRASV2_BAROMETER_MS5607_H

#include <cstdint>
#include "MS5607.h"
#include "Barometer.h"


class Barometer_MS5607 : public Barometer {
public:
    int8_t begin() override;
    int8_t readData() override;
private:
    MS5607 _sensor;
};


#endif //MRASV2_BAROMETER_MS5607_H
