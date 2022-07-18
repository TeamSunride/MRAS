//
// Created by robosam2003 2022
//


#ifndef VECTOR_LIBRARY_H
#define VECTOR_LIBRARY_H



#include <iostream>
#include <cmath>

#define PI 3.14159265358979323846

template<typename T, unsigned int s>
class Vector {
public:
    Vector();
    // constructors
//    explicit Vector(int size);

    Vector(std::initializer_list<T> lst);
    int getSize() const;

    // Copy
    /**
     * @brief Copy constructor for Vector, note that Vector is a resource handler, so a copy constructor is needed such that copying is not a memberwise copy
     * @param a
     */
    Vector(const Vector& a);            // copy constructor

    /**
     * @brief Copy assignment constructor for Vector. Usage: Vector<int> v1 {1, 2, 3}; Vector<int> v2 = v1;
     * @param a
     * @return
     */
    Vector& operator=(const Vector& a); // copy assignment


    // Move
    /**
     * @brief Move constructor for Vector.
     * @param a - an rvalue reference to a Vector
     */
    Vector(Vector&& a) noexcept ;            // move constructor

    /**
     * @brief Move assignment constructor for Vector. Usage: Vector<int> v1 {1, 2, 3}; Vector<int> v2 = std::move(v1);
     * @param a
     * @return
     */
    Vector& operator=(Vector&& a) noexcept ; // move assignment

    // operators
    /**
     * @brief operator []
     * @param i
     * @return the i-th element of the vector
     */
    T& operator[](size_t i); /// const specifier means "Do not modify in this scope" - i.e. we do not modify member variables in this scope

    const T& operator[](size_t i) const;
    /**
     * @brief operator / : divide all elements by a scalar
     * @param scalar
     * @return the vector divided by the scalar
     */
    Vector<T, s> operator/(double scalar) const;

    /**
     * @brief operator /= : divide equals all elements by a scalar
     * @param scalar
     * @return reference to the caller vector
     */
    Vector<T, s> & operator/=(double scalar);

    /**
     * @brief operator * : multiply all elements by a scalar
     * @param scalar
     * @return the vector multiplied by the scalar
     */
    Vector<T, s> operator*(double scalar) const;

    /**
     * @brief operator *= : multiply equals all elements by a scalar
     * @param scalar
     * @return reference to the caller vector
     */
    Vector<T, s>& operator*=(double scalar);

    /**
     * @brief operator += : add equals two vectors of the same size together
     * @param v
     * @return reference to the caller vector
     */
    Vector<T, s>& operator+=(Vector<T, s> v);
    /**
     * @brief operator -= : subtract v from caller vector
     * @param v
     * @return reference to the caller vector
     */
    Vector<T, s>& operator-=(Vector<T, s> v);

    /**
     * @brief operator + : add two vectors of the same size together
     * @param v
     * @return the result of the sum
     */
    Vector<T, s> operator+(Vector<T, s> v) const;

    /**
     * @brief operator - : subtract v from caller vector
     * @param v
     * @return the result of the sum
     */
    Vector<T, s>operator-(Vector<T, s> v);

    // TODO: iterators? begin functions for range-for?

    // Vector operations
    /**
     * @brief calculate the norm of a vector
     * @return the norm of the caller vector
     */
    double norm() const;

    /**
     * @brief calculate the dot product of the caller vector and v
     * @param v
     * @return the dot (scalar) product of the caller vector and v
     */
    double dot(Vector<T, s> v) const;

    /**
     * @brief normalise the caller vector
     * @return reference to the normalised caller vector
     */
    Vector<T, s>& normalize();

    /**
     * @brief normalise the caller vector
     * @return the normalised caller vector.
     */
    Vector<T, s> normalized() const;

    /**
     * @brief calculate the cross product of the caller vector and v
     * @param v
     * @return the cross product of the caller vector and v
     */
    Vector<T, s> cross(Vector<T, s> v) const;

    /**
     * @brief calculate the direction cosines triad of the caller vector
     * @param v
     * @return the direction cosines triad of the caller vector
     */
    Vector<T, s> directionCosines() const;

    // TODO: Rotation matrices etc

    ~Vector() = default; // destructor - implicit definition
//protected:
    T elem[s];
};


#include "Vector.tpp"

#endif //VECTOR_LIBRARY_H
