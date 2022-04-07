//
// Created by Tom Danvers on 06/04/2022.
// 2022 TeamSunride.
//

#ifndef MRASV2_VECTOR3D_H
#define MRASV2_VECTOR3D_H


template <typename T>
class Vector3D {
public:
    T _dimensions[3];
    T getX();
    T getY();
    T getZ();

    void setX(T value);
    void setY(T value);
    void setZ(T value);

    Vector3D<double> divideScalar(double factor);
};



template<typename T>
Vector3D<double> Vector3D<T>::divideScalar(double factor) {
    Vector3D<double> returnVector{};
    for (int i=0; i<3; i++) {
        returnVector._dimensions[i] = _dimensions[i] / factor;
    }
    return returnVector;
}

template<typename T>
T Vector3D<T>::getX() {
    return _dimensions[0];
}

template<typename T>
T Vector3D<T>::getY() {
    return _dimensions[1];
}

template<typename T>
T Vector3D<T>::getZ() {
    return _dimensions[2];
}

template<typename T>
void Vector3D<T>::setX(T value) {
    _dimensions[0] = value;
}

template<typename T>
void Vector3D<T>::setY(T value) {
    _dimensions[1] = value;
}

template<typename T>
void Vector3D<T>::setZ(T value) {
    _dimensions[2] = value;
}


#endif //MRASV2_VECTOR3D_H
