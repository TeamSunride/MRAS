//
// Created by Tom Danvers on 13/12/2022.
//

#ifndef MRAS_ACCELEROMETERDATAMSG_H
#define MRAS_ACCELEROMETERDATAMSG_H


#include "SystemMessage.h"
#include "Vector.h"

/**
 * @brief Message sent by the accelerometer to the system
 *
 * The units of the acceleration are m/s^2 and are stored as a Vector<float, 3>
 */
struct AccelerometerDataMsg : public SystemMessage {
    explicit AccelerometerDataMsg(SystemMessageType accel_msg_type) : SystemMessage(accel_msg_type) {}

    /**
     * @brief The acceleration in m/s^2
     *
     * The acceleration is stored as a Vector<float, 3>
     * where the first element is the x-axis, the second is the y-axis and the third is the z-axis
     */
    Vector<float, 3> acceleration = {0, 0, 0};
};

#endif //MRAS_ACCELEROMETERDATAMSG_H
