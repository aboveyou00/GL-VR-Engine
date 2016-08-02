#ifndef VECTOR_H
#define VECTOR_H
#pragma once

// Brandon Slade
// 5/20/2016
// Vector.h
// A templated variable-length vector structure. Defaults to using float components

#include <iostream>
#include <assert.h>
#include "vbo_attribs.h"

template <unsigned dimension, typename ElemT = float>//, typename = std::enable_if_t<(dimension > 0)>>
struct Vector
{
public:
	template <int dimension_other>
	Vector(Vector<dimension_other> d)
	{
		for (auto q = 0; q < dimension_other; q++)
			values[q] = d[q];
	}
	
	template <typename... Args>
    Vector(Args... vals)
    {
        for (auto q = 0; q < dimension; q++)
            values[q] = 0;
        initialize(vals...);
    }
    Vector(ElemT *vals, int valn = dimension)
    {
        assert(valn <= dimension && valn >= 0);
        for (auto q = 0; q < valn; q++)
            values[q] = *(vals + q);
        for (auto q = valn; q < dimension; q++)
            values[q] = 0;
    }
    ~Vector()
    {
    }

    ElemT LengthSquared() const
    {
        ElemT sum = 0.f;
        for (auto q = 0; q < dimension; q++)
            sum += values[q] * values[q];
        return sum;
    }
    inline ElemT Length() const
    {
        return sqrt(LengthSquared());
    }
    inline ElemT Angle() const
    {
        static_assert(dimension == 2, "Vector.Angle is only available for two-dimensional vectors");
        return atan2(values[1], values[0]);
    }

    Vector<dimension, ElemT> Normalized(ElemT len = 1) const
    {
        auto length = Length();
        if (length == 0)
        {
            //GameLogger::Current()->Log(LogType::Error, "Tried to normalize the zero vector. Returning (1, 0, ...)\n");
            auto result = Vector<dimension, ElemT>();
            result.values[0] = 1;
            return result;
        }
        return (*this / length) * len;
    }
    ElemT Dot(const Vector<dimension, ElemT> &right) const
    {
        ElemT sum = 0.f;
        for (auto q = 0; q < dimension; q++)
            sum += values[q] * right[q];
        return sum;
    }

    template <typename = std::enable_if_t<dimension == 3>>
    inline Vector<dimension, ElemT> Cross(const Vector<dimension> &right) const
    {
		return Vector<3, ElemT> {
			values[1] * right[2] - values[2] * right[1],
			values[2] * right[0] - values[0] * right[2],
			values[0] * right[1] - values[1] * right[0]
		};
    }
    
    Vector<dimension, ElemT> Perpendicular(bool cw = true) const
    {
        static_assert(dimension == 2, "Vector.Perpendicular is only available for two-dimensional vectors");
        if (cw) return Vector<2, ElemT> { values[1], -values[0] };
        else return Vector<2, ElemT> { -values[1], values[0] };
    }

    Vector<dimension, ElemT> Projection(const Vector<dimension, ElemT> &onto) const
    {
        auto lengthSquared = LengthSquared();
        if (lengthSquared == 0)
        {
            //GameLogger::Current()->Log(LogType::Error, "Tried to project a zero-length vector. Returning (0, 0, ...)\n");
            return Vector<dimension, ElemT>();
        }
        return (onto * *this) * *this / LengthSquared();
    }
    Vector<dimension, ElemT> Rejection(const Vector<dimension, ElemT> &onto) const
    {
        Vector2 proj, rej;
        ProjectionRejection(onto, proj, rej);
        return rej;
    }
    inline void ProjectionRejection(const Vector<dimension, ElemT> onto, Vector<dimension, ElemT> &proj, Vector<dimension, ElemT> &rej) const
    {
        proj = Projection(onto);
        rej = onto - proj;
    }

	bool operator==(const Vector<dimension, ElemT>& other) const
	{
		for (int i = 0; i < dimension; i++)
			if (other[i] != values[i])
				return false;
		return true;
	}

    friend Vector<dimension, ElemT> operator-(Vector<dimension, ElemT> &operand)
    {
        auto result = Vector<dimension, ElemT>();
        for (auto q = 0; q < dimension; q++)
            result.values[q] = -operand[q];
        return result;
    }

    friend Vector<dimension, ElemT> operator*(ElemT left, const Vector<dimension, ElemT> &right)
    {
        auto result = Vector<dimension, ElemT>();
        for (auto q = 0; q < dimension; q++)
            result.values[q] = left * right[q];
        return result;
    }
    friend Vector<dimension, ElemT> operator*(const Vector<dimension, ElemT> &left, ElemT right)
    {
        auto result = Vector<dimension, ElemT>();
        for (auto q = 0; q < dimension; q++)
            result.values[q] = left[q] * right;
        return result;
    }
    friend Vector<dimension, ElemT> operator/(const Vector<dimension, ElemT> &left, ElemT right)
    {
        if (right == 0)
        {
            //GameLogger::Current()->Log(LogType::Error, "Tried to divide a vector by zero. Returning (0, 0, ...)");
            return Vector<dimension, ElemT>();
        }
        auto result = Vector<dimension, ElemT>();
        for (auto q = 0; q < dimension; q++)
            result.values[q] = left[q] / right;
        return result;
    }

    friend Vector<dimension, ElemT> operator+(const Vector<dimension, ElemT> &left, const Vector<dimension, ElemT> &right)
    {
        auto result = Vector<dimension, ElemT>();
        for (auto q = 0; q < dimension; q++)
            result.values[q] = left[q] + right[q];
        return result;
    }
    friend Vector<dimension, ElemT> operator-(const Vector<dimension, ElemT> &left, const Vector<dimension, ElemT> &right)
    {
        auto result = Vector<dimension, ElemT>();
        for (auto q = 0; q < dimension; q++)
            result.values[q] = left[q] - right[q];
        return result;
    }
    inline friend ElemT operator*(const Vector<dimension, ElemT> &left, const Vector<dimension, ElemT> &right)
    {
        return left.Dot(right);
    }

    inline Vector<dimension, ElemT> &operator=(const Vector<dimension, ElemT> &right)
    {
        for (auto q = 0; q < dimension; q++)
            values[q] = right[q];
        return *this;
    }
    friend Vector<dimension, ElemT> &operator*=(Vector<dimension, ElemT> &left, ElemT right)
    {
		return (left = left * right);
    }
	friend Vector<dimension, ElemT> &operator/=(Vector<dimension, ElemT> &left, ElemT right)
	{
		return (left = left / right);
	}
    friend Vector<dimension, ElemT> &operator+=(Vector<dimension, ElemT> &left, const Vector<dimension, ElemT> &right)
	{
        return (left = left + right);
    }
    friend Vector<dimension, ElemT> &operator-=(Vector<dimension, ElemT> &left, const Vector<dimension, ElemT> &right)
    {
        return (left = left - right);
    }
    
    friend bool operator==(Vector<dimension, ElemT> &left, Vector<dimension, ElemT> &right)
    {
        for (size_t q = 0; q < dimension; q++)
        {
            if (!(left[q] == right[q])) return false;
        }
        return true;
    }
    friend bool operator!=(Vector<dimension, ElemT> &left, Vector<dimension, ElemT> &right)
    {
        for (size_t q = 0; q < dimension; q++)
        {
            if (left[q] != right[q]) return true;
        }
        return false;
    }

    inline friend std::ostream &operator<<(std::ostream &stream, const Vector<dimension, ElemT> &vec)
    {
        stream << "(" << vec[0];
        for (auto q = 1; q < dimension; q++)
            stream << ", " << vec[q];
        return stream << ")";
    }

    inline ElemT operator[](int idx) const
    {
        return values[idx];
    }

    inline const ElemT *getAddr() const
    {
        return values;
    }

private:
    ElemT values[dimension];

    //Constructor helpers:
    template <int idx = 0, typename T, typename... Args>
    inline void initialize(T val, Args... args)
    {
        values[idx] = (ElemT)val;
        initialize<idx + 1>(args...);
    }
    template <int idx = 0, typename T>
    inline void initialize(T val)
    {
        values[idx] = (ElemT)val;
    }
    inline void initialize()
    {
    }

};

#endif //ndef VECTOR_H
