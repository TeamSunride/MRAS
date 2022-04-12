//
// Created by Tom Danvers on 12/04/2022.
// 2022 TeamSunride.
//

#include "Vector3D.h"

Vector3D Vector3D::divideScalar(float factor) {
    Vector3D returnVector{};
    for (int i=0; i<3; i++) {
        returnVector._dimensions[i] = _dimensions[i] / factor;
    }
    return returnVector;
}

float Vector3D::getX() {
    return _dimensions[0];
}

float Vector3D::getY() {
    return _dimensions[1];
}

float Vector3D::getZ() {
    return _dimensions[2];
}

void Vector3D::setX(float value) {
    _dimensions[0] = value;
}

void Vector3D::setY(float value) {
    _dimensions[1] = value;
}

void Vector3D::setZ(float value) {
    _dimensions[2] = value;
}