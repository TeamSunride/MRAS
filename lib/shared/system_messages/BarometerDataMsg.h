//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_BAROMETERDATAMSG_H
#define MRAS_BAROMETERDATAMSG_H

#include "SystemMessage.h"

/**
 * @brief Message sent by the barometer to the system
 *
 * The units of the pressure are Pa and the temperature is in degrees Celsius
 */
struct BarometerDataMsg : public SystemMessage {
    explicit BarometerDataMsg() : SystemMessage(BarometerDataMsg_t) {}

    /**
     * @brief The pressure in Pa
     */
    float pressure = 0;

    /**
     * @brief The temperature in degrees Celsius
     */
    float temperature = 0;
};

#endif //MRAS_BAROMETERDATAMSG_H
