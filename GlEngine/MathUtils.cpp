#include "stdafx.h"
#include "MathUtils.h"

namespace GlEngine
{
    namespace Util
    {
        constexpr float radToDeg(const float rad)
        {
            return (float)(rad / PI * 180);
        }
        constexpr float degToRad(const float deg)
        {
            return (float)(deg * PI / 180);
        }

        constexpr double radToDeg_d(const double rad)
        {
            return rad / PI * 180;
        }
        constexpr double degToRad_d(const double deg)
        {
            return deg * PI / 180;
        }
    }
}

float operator "" rad(long double angle)
{
    return static_cast<float>(angle);
}
float operator "" deg(unsigned long long angle)
{
    return GlEngine::Util::degToRad((float)angle);
}
float operator "" deg(long double angle)
{
    return GlEngine::Util::degToRad((float)angle);
}

double operator "" rad_d(long double angle)
{
    return static_cast<double>(angle);
}
double operator "" deg_d(unsigned long long angle)
{
    return GlEngine::Util::degToRad_d((double)angle);
}
double operator "" deg_d(long double angle)
{
    return GlEngine::Util::degToRad_d((double)angle);
}

// Moller-Trumbore ray-triangle intersection algorithm
bool triangleRayIntersects(Vector<3> t1, Vector<3> t2, Vector<3> t3, Vector<3> rayOrigin, Vector<3> rayDirection, float* outDistance)
{
    static const float epsilon = 0.000001f;

    auto edge1 = t2 - t1;
    auto edge2 = t3 - t1;

    auto P = rayDirection.Cross(edge2);

    float det = edge1.Dot(P);
    if (det < epsilon && det > -epsilon) // ray is parallel to triangle
        return false;

    float invDet = 1.f / det;
    
    auto T = rayOrigin - t1;
    float u = T.Dot(P) * invDet;

    if (u < 0.f || u > 1.f) // no intersection
        return false;

    auto Q = T.Cross(edge1);
    float v = rayDirection.Dot(Q);

    if (v < 0.f || u + v > 1.f) // no intersection
        return false;

    float t = edge2.Dot(Q) * invDet;
    if (t > epsilon)
    {
        if (outDistance != nullptr)
            *outDistance = t;
        return true;
    }

    return false; // wrong side
}
