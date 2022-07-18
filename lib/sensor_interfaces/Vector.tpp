//
// Created by robosam2003 on 30/06/2022.
//
#include "Vector.h"

// constructors
template<typename T, unsigned int s>
Vector<T, s>::Vector() {
    for (int i=0;i<s;i++) elem[i] = 0;
}

template<typename T, unsigned int s>
Vector<T, s>::Vector(std::initializer_list<T> lst) { // usage: Vector<int> vec {1, 2 ,3}
    for (int i=0;i<s;i++) {
        elem[i] = lst.begin()[i]; // instead of doing std::copy(lst.begin(), lst.end(), elem.begin())
        // this way we don't write to unreserved memory :)
    }
}


//// default constructor - defaults to size 3 - needed for implementations like e.g. Fifo<Vector<double>>
//template<typename T, unsigned int s>
//Vector<T, s>::Vector() {
//    elem = new T[3]; // default to 3
//    sz = 3;
//    for (int i=0;i<sz;i++) elem[i] = 0;
//}

// operators
template<typename T, unsigned int s>
T &Vector<T, s>::operator[](size_t i) {
    return elem[i];
}

template<typename T, unsigned int s>
const T& Vector<T, s>::operator[](size_t i) const {
    return elem[i];
}

template<typename T, unsigned int s>
int Vector<T, s>::getSize() const {
    return s;
}

template<typename T, unsigned int s>
Vector<T, s> Vector<T, s>::operator*(double scalar) const {
    Vector<T, s> v;
    for (int i=0; i<s; i++) {
        v[i] = elem[i] * scalar;
    }
    return v;

}

template<typename T, unsigned int s>
Vector<T, s> Vector<T, s>::operator/(double scalar) const {
    Vector<T, s> v;
    for (int i=0; i<s; i++) {
        v[i] = elem[i] / scalar;
    }
    return v;
}

template<typename T, unsigned int s>
Vector<T, s>& Vector<T, s>::operator/=(double scalar) {
    for (int i=0; i<s; i++) {
        elem[i] /= scalar;
    }
    return *this;
}

template<typename T, unsigned int s>
Vector<T, s> &Vector<T, s>::operator*=(double scalar) {
    for (int i=0; i<s; i++) {
        elem[i] *= scalar;
    }
    return *this;
}

template<typename T, unsigned int s>
Vector<T, s> &Vector<T, s>::operator+=(Vector<T, s> v)  {
    for (int i=0; i<s; i++) {
        elem[i] += v[i];
    }
    return *this;
}

template<typename T, unsigned int s>
Vector<T, s> &Vector<T, s>::operator-=(Vector<T, s> v) {
    for (int i=0; i<s; i++) {
        elem[i] -= v[i];
    }
    return *this;
}

template<typename T, unsigned int s>
Vector<T, s> Vector<T, s>::operator+(Vector<T, s> v) const{
    Vector<T, s> rv;
    for (int i=0; i<s; i++) {
        rv[i] = elem[i] + v[i];
    }
    return rv;
}

template<typename T, unsigned int s>
Vector<T, s> Vector<T, s>::operator-(Vector<T, s> v) {
    Vector<T, s> rv;
    for (int i=0; i<s; i++) {
        rv[i] = elem[i] - v[i];
    }
    return rv;
}


// Vector operations
template<typename T, unsigned int s>
double Vector<T, s>::norm() const {
    double sum = 0;
    for (int i=0; i<s; i++) {
        sum += elem[i] * elem[i];
    }
    return sqrt(sum);
}

template<typename T, unsigned int s>
double Vector<T, s>::dot(Vector<T, s> v) const {
    double sum = 0;
    for (int i=0; i<s; i++) {
        sum += elem[i] * v[i];
    }
    return sum;
}

template<typename T, unsigned int s>
Vector<T, s> &Vector<T, s>::normalize() {
    double norm = this->norm();
    for (int i=0; i<s; i++) {
        elem[i] /= norm;
    }
    return *this;
}

template<typename T, unsigned int s>
Vector<T, s> Vector<T, s>::normalized() const {
    double norm = this->norm();
    Vector<T, s> v;
    for (int i=0; i<s; i++) {
        v[i] = elem[i] / norm;
    }
    return v;
}

template<typename T, unsigned int s>
Vector<T, s> Vector<T, s>::cross(Vector<T, s> v) const {
    /// only works for 3D vectors
    Vector<T, s> rv = {0, 0, 0};
    rv[0] = elem[1] * v[2] - elem[2] * v[1]; // i
    rv[1] = elem[2] * v[0] - elem[0] * v[2]; // j
    rv[2] = elem[0] * v[1] - elem[1] * v[0]; // k
    return rv;
}

template<typename T, unsigned int s>
Vector<T, s> Vector<T, s>::directionCosines() const {
    /// Note that: l^2 + m^2 + n^2 = 1
    Vector<T, s> rv = {0, 0, 0};
    double norm = this->norm();
    rv[0] = elem[0] / norm; /// l = cos(alpha) = x/r
    rv[1] = elem[1] / norm; /// m = cos(beta) = y/r
    rv[2] = elem[2] / norm; /// n = cos(gamma) = z/r
    return rv;
}



// copy constructor
template<typename T, unsigned int s>
Vector<T, s>::Vector(const Vector<T, s>& a) {
    // copy elements
    for (int i=0;i<s;i++) {
        elem[i] = a.elem[i];
    }
}

// copy assignment
template<typename T, unsigned int s>
Vector<T, s> &Vector<T, s>::operator=(const Vector<T, s> &a) {
    for (int i=0;i<s;i++){
        elem[i] = a.elem[i];
    }
    return *this;
}


// move constructor
template<typename T, unsigned int s>
Vector<T, s>::Vector(Vector<T, s> &&a) noexcept {
    for (int i=0; i<s; i++) {
        elem[i] = a.elem[i];
    }
}

// move assignment
template<typename T, unsigned int s>
Vector<T, s>& Vector<T, s>::operator=(Vector<T, s> &&a)  noexcept {
    for (int i=0; i<s; i++) {
        elem[i] = a.elem[i];
    }
    return *this;
}


