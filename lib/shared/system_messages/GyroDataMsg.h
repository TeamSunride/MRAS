//
// Created by Tom Danvers on 17/12/2022.
//

#ifndef MRAS_GYRODATAMSG_H
#define MRAS_GYRODATAMSG_H

#include "SystemMessage.h"
#include "Vector.h"

/**
 * @brief Message sent by the gyroscope to the system
 *
 * The units of the angular velocity are rad/s and are stored as a Vector<float, 3>
 */
struct GyroDataMsg : public SystemMessage {
    GyroDataMsg() : SystemMessage(GyroDataMsg_t) {}

    /**
     * @brief The angular velocity in rad/s
     *
     * The angular velocity is stored as a Vector<float, 3>
     * where the first element is the x-axis, the second is the y-axis and the third is the z-axis
     */
    Vector<float, 3> gyro = {0, 0, 0};
};

#endif //MRAS_GYRODATAMSG_H
