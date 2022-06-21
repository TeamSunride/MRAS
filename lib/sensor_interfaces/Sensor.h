//
// Created by Tom Danvers on 05/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_SENSOR_H
#define MRASV2_SENSOR_H

#include <cstdint>

/*
 * Global sensor interface, to be inherited by sensor types, such as Barometer, Accelerometer, etc.
 */
class Sensor {
public:
    /*
     * Read data from the sensor and store it within the derived class of Sensor, for later use in other parts of the
     * program.
     *
     * Return 0 upon success, else return a status code
     */
    virtual int8_t readData() = 0;

    /*
     * Initialise the sensor
     *
     * Return 0 upon success, else return a status code
     */
    virtual int8_t begin() = 0;

    /*
     * Perform a self test of the sensor. Return 0 if the sensor passes the self test, else return a status code
     *
     * If the sensor does not have a self test, then return -1
     */
    virtual int8_t selfTest() {
        return -1;
    };
};

#endif //MRASV2_SENSOR_H
