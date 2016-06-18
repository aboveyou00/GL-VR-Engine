#ifndef VECTOR_H
#define VECTOR_H
#pragma once

// Brandon Slade
// 5/20/2016
// Vector.h
// A templated variable-length vector structure with float components

#include <iostream>
#include <assert.h>

namespace GlEngine
{
    template <unsigned dimension>//, typename = std::enable_if_t<(dimension > 0)>>
    struct Vector
    {
    public:
        template <typename... Args>
        Vector(Args... vals)
        {
            for (auto q = 0; q < dimension; q++)
                values[q] = 0;
            initialize(vals...);
        }
        Vector(float *vals, int valn = dimension)
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

        float LengthSquared() const
        {
            float sum = 0.f;
            for (auto q = 0; q < dimension; q++)
                sum += values[q] * values[q];
            return sum;
        }
        inline float Length() const
        {
            return sqrt(LengthSquared());
        }
        template <typename = std::enable_if_t<dimension == 2>>
        inline float Angle() const
        {
            return atan2(values[1], values[0]);
        }

        Vector<dimension> Normalized(float len = 1) const
        {
            auto length = Length();
            if (length == 0)
            {
                //GameLogger::Current()->Log(LogType::Error, "Tried to normalize the zero vector. Returning (1, 0, ...)\n");
                auto result = Vector<dimension>();
                result.values[0] = 1;
                return result;
            }
            return (*this / length) * len;
        }
        float Dot(const Vector<dimension> &right) const
        {
            float sum = 0.f;
            for (auto q = 0; q < dimension; q++)
                sum += values[q] * right[q];
            return sum;
        }

        template <typename = std::enable_if_t<dimension == 3>>
        inline Vector<dimension> Cross(const Vector<dimension> &right) const
        {
			return Vector<3> {
				values[1] * right[2] - values[2] * right[1],
					values[2] * right[0] - values[0] * right[2],
					values[0] * right[1] - values[1] * right[0]
			};
        }

        template <typename = std::enable_if_t<dimension == 2>>
        Vector<dimension> Perpendicular(bool cw = true) const
        {
            if (cw) return Vector<2> { values[1], -values[0] };
            else return Vector<2> { -values[1], values[0] };
        }

        Vector<dimension> Projection(const Vector<dimension> &onto) const
        {
            auto lengthSquared = LengthSquared();
            if (lengthSquared == 0)
            {
                //GameLogger::Current()->Log(LogType::Error, "Tried to project a zero-length vector. Returning (0, 0, ...)\n");
                return Vector<dimension>();
            }
            return (onto * *this) * *this / LengthSquared();
        }
        Vector<dimension> Rejection(const Vector<dimension> &onto) const
        {
            Vector2 proj, rej;
            ProjectionRejection(onto, proj, rej);
            return rej;
        }
        inline void ProjectionRejection(const Vector<dimension> onto, Vector<dimension> &proj, Vector<dimension> &rej) const
        {
            proj = Projection(onto);
            rej = onto - proj;
        }

        friend Vector<dimension> operator-(Vector<dimension> &operand)
        {
            auto result = Vector<dimension>();
            for (auto q = 0; q < dimension; q++)
                result.values[q] = -operand[q];
            return result;
        }

        friend Vector<dimension> operator*(float left, const Vector<dimension> &right)
        {
            auto result = Vector<dimension>();
            for (auto q = 0; q < dimension; q++)
                result.values[q] = left * right[q];
            return result;
        }
        friend Vector<dimension> operator*(const Vector<dimension> &left, float right)
        {
            auto result = Vector<dimension>();
            for (auto q = 0; q < dimension; q++)
                result.values[q] = left[q] * right;
            return result;
        }
        friend Vector<dimension> operator/(const Vector<dimension> &left, float right)
        {
            if (right == 0)
            {
                //GameLogger::Current()->Log(LogType::Error, "Tried to divide a vector by zero. Returning (0, 0, ...)");
                return Vector<dimension>();
            }
            auto result = Vector<dimension>();
            for (auto q = 0; q < dimension; q++)
                result.values[q] = left[q] / right;
            return result;
        }

        friend Vector<dimension> operator+(const Vector<dimension> &left, const Vector<dimension> &right)
        {
            auto result = Vector<dimension>();
            for (auto q = 0; q < dimension; q++)
                result.values[q] = left[q] + right[q];
            return result;
        }
        friend Vector<dimension> operator-(const Vector<dimension> &left, const Vector<dimension> &right)
        {
            auto result = Vector<dimension>();
            for (auto q = 0; q < dimension; q++)
                result.values[q] = left[q] - right[q];
            return result;
        }
        inline friend float operator*(const Vector<dimension> &left, const Vector<dimension> &right)
        {
            return left.Dot(right);
        }

        inline Vector<dimension> &operator=(const Vector<dimension> &right)
        {
            for (auto q = 0; q < dimension; q++)
                values[q] = right[q];
            return *this;
        }
        friend Vector<dimension> &operator*=(Vector<dimension> &left, float right)
        {
            for (auto q = 0; q < dimension; q++)
                left.values[q] *= right;
            return left;
        }
        friend Vector<dimension> &operator+=(Vector<dimension> &left, const Vector<dimension> &right)
        {
            for (auto q = 0; q < dimension; q++)
                left.values[q] += right[q];
            return left;
        }
        friend Vector<dimension> &operator-=(Vector<dimension> &left, const Vector<dimension> &right)
        {
            for (auto q = 0; q < dimension; q++)
                left.values[q] -= right[q];
            return left;
        }
        friend Vector<dimension> &operator*=(Vector<dimension> &left, const Vector<dimension> &right)
        {
            left = left * right;
        }

        inline friend std::ostream &operator<<(std::ostream &stream, const Vector<dimension> &vec)
        {
            stream << "(" << vec[0];
            for (auto q = 1; q < dimension; q++)
                stream << ", " << vec[q];
            return stream << ")";
        }

        inline float operator[](int idx) const
        {
            return values[idx];
        }

        inline const float *getAddr() const
        {
            return values;
        }

    private:
        float values[dimension];

        //Constructor helpers:
        template <int idx = 0, typename T, typename... Args>
        inline void initialize(T val, Args... args)
        {
            values[idx] = (float)val;
            initialize<idx + 1>(args...);
        }
        template <int idx = 0, typename T>
        inline void initialize(T val)
        {
            values[idx] = (float)val;
        }
        inline void initialize()
        {
        }
    };
}

#endif //ndef VECTOR_H
