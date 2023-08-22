//
// Created by Nikilesh Ramesh on 22/08/2023.
//

#ifndef MRAS_ORIENTATIONDATAMSG_H
#define MRAS_ORIENTATIONDATAMSG_H

#include "Vector.h"
#include "SystemMessage.h"

/**
 * @brief Message containing the orientation data of the rocket
 *
 * Hamilton convention which has the scalar term first and are stored as a Vector<float, 4>
 */
struct OrientationDataMsg : public SystemMessage {
    OrientationDataMsg() : SystemMessage(OrientationDataMsg_t) {}
    /**
     * @brief Quaternions are dimensionless {?}
     *
     * Quaternion is stored as a Vector<float, 4>
     * where the first element is the scalar term, second, third and fourth are coefficients of the i, j and k terms respectively
     */
    Vector<float, 4> quaternion = {1, 0, 0, 0};
};

#endif //MRAS_ORIENTATIONDATAMSG_H
