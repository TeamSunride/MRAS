//
// Created by Tom Danvers on 06/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_VECTOR3D_H
#define MRASV2_VECTOR3D_H


class Vector3D {
public:
    float _dimensions[3];
    float getX() const;
    float getY() const;
    float getZ() const;

    void setX(float value);
    void setY(float value);
    void setZ(float value);

    Vector3D divideScalar(float factor);
};


#endif //MRASV2_VECTOR3D_H
