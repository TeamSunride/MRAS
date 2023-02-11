//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_MAGNETOMETERDATAMSG_H
#define MRAS_MAGNETOMETERDATAMSG_H


#include "SystemMessage.h"
#include "Vector.h"

/**
 * @brief Message sent by the magnetometer to the system
 *
 * The units of the magnetic field are Gauss and are stored as a Vector<float, 3>. One Gauss is equal to 1e-4 Tesla
 */
struct MagnetometerDataMsg : public SystemMessage {
    MagnetometerDataMsg() : SystemMessage(MagnetometerDataMsg_t) {}

    /**
     * @brief The magnetic field in Gauss (1e-4 Tesla)
     *
     * The magnetic field is stored as a Vector<float, 3>
     * where the first element is the x-axis, the second is the y-axis and the third is the z-axis
     */
    Vector<float, 3> mag = {0, 0, 0};
};

#endif //MRAS_MAGNETOMETERDATAMSG_H
