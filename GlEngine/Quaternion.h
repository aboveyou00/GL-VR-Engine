#pragma once

#include "Vector.h"

template<typename ElemT = float>
class Quaternion
{
public:
    Quaternion(ElemT real, ElemT i, ElemT j, ElemT k)
        : _real(real), _i(i), _j(j), _k(k)
    {
    }
    Quaternion(ElemT i, ElemT j, ElemT k)
        : Quaternion(0, i, j, k)
    {
    }
    Quaternion(Vector<4, ElemT> data)
        : Quaternion(data[0], data[1], data[2], data[3])
    {
    }
    Quaternion(ElemT theta, Vector<3, ElemT> axis)
    {
        ElemT sinHalfTheta = sin(theta / 2);
        ElemT cosHalfTheta = cos(theta / 2);
        _real = cosHalfTheta;
        _i = axis[0] * sinHalfTheta;
        _j = axis[1] * sinHalfTheta;
        _k = axis[2] * sinHalfTheta;
    }

    inline ElemT real()
    {
        return _real;
    }
    inline ElemT i()
    {
        return _i;
    }
    inline ElemT j()
    {
        return _j;
    }
    inline ElemT k()
    {
        return _k;
    }

    Quaternion Inverse()
    {
        return Quaternion(_real, -_i, -_j, -_k);
    }

    Vector<4, ElemT> ToVector()
    {
        return new Vector<4, ElemT>(_real, _i, _j, _k);
    }

    Matrix<4, 4, ElemT> ToMatrix()
    {
        return Matrix<4, 4, ElemT>(
            1 - 2 * _j*_j - 2 * _k*_k, 2 * _i*_j - 2 * _k*_real , 2 * _i*_k + 2 * _j*_real , 0,
            2 * _i*_j + 2 * _k*_real , 1 - 2 * _i*_i - 2 * _k*_k, 2 * _j*_k - 2 * _i*_real , 0,
            2 * _i*_k - 2 * _j*_real , 2 * _j*_k + 2 * _i*_real , 1 - 2 * _i*_i - 2 * _j*_j, 0,
            0                        , 0                        , 0                        , 1
        );
    }

    Vector<3, ElemT> Apply(Vector<3, ElemT> vector)
    {
        return (*this) * vector * Inverse();
    }

    friend Quaternion<ElemT> operator+ (const Quaternion<ElemT>& first, const Quaternion<ElemT>& second)
    {
        return Quaternion<ElemT>(first._real + second._real, first._i + second._i, first._j + second._j, first._k + second._k);
    }

    friend Quaternion<ElemT> operator* (const Quaternion<ElemT>& first, const Quaternion<ElemT>& second)
    {
        ElemT resultReal = first._real * second._real - first._i    * second._i    - first._j    * second._j    - first._k    * second._k;
        ElemT resultI    = first._real * second._i    + first._i    * second._real + first._j    * second._k    - first._k    * second._j;
        ElemT resultJ    = first._real * second._j    - first._i    * second._k    + first._j    * second._real + first._k    * second._i;
        ElemT resultK    = first._real * second._k    + first._i    * second._j    - first._j    * second._i    + first._k    * second._real;
        return Quaternion<ElemT>(resultReal, resultI, resultJ, resultK);
    }

    friend Vector<4, ElemT> operator* (const Quaternion<ElemT>& first, const Vector<4, ElemT>& second)
    {
        Quaternion<ElemT> result = first * Quaternion<ElemT>(second);
        return result.ToVector();
    }

    friend Vector<4, ElemT> operator* (const Vector<4, ElemT>& first, const Quaternion<ElemT>& second)
    {
        Quaternion<ElemT> result = Quaternion<ElemT>(first) * second;
        return result.ToVector();
    }

    friend Vector<3, ElemT> operator* (const Vector<3, ElemT>& first, const Quaternion<ElemT>& second)
    {
        Quaternion<ElemT> result = Quaternion<ElemT>(0, first._i, first._j, first._k) * second;
        return Vector<3, ElemT>(result._i, result._j, result._k);
    }

    friend Vector<3, ElemT> operator* (const Quaternion<ElemT>& first, const Vector<3, ElemT>& second)
    {
        Quaternion<ElemT> result = first * Quaternion<ElemT>(0, second[0], second[1], second[2]);
        return Vector<3, ElemT>(result._i, result._j, result._k);
    }

    friend Quaternion<ElemT> operator* (const Quaternion<ElemT>& first, ElemT scalar)
    {
        return Quaternion<ElemT>(first._real * scalar, first._i * scalar, first._j * scalar, first._k * scalar);
    }

    friend Quaternion<ElemT> operator* (ElemT scalar, const Quaternion<ElemT> second)
    {
        return second * scalar;
    }

    friend Vector<4, ElemT>& operator*= (Vector<4, ElemT>& first, const Quaternion<ElemT>& second)
    {
        first = first * second;
        return first;
    }

    friend Vector<3, ElemT>& operator*= (Vector<3, ElemT>& first, const Quaternion<ElemT>& second)
    {
        first = first * second;
        return first;
    }

    friend Quaternion<ElemT>& operator*= (Quaternion<ElemT>& first, const ElemT scalar)
    {
        first = first * scalar;
        return first;
    }

    friend Quaternion<ElemT>& operator*= (Quaternion<ElemT>& first, const Quaternion<ElemT>& second)
    {
        first = first * second;
        return first;
    }

private:
    ElemT _real;
    ElemT _i;
    ElemT _j;
    ElemT _k;
};