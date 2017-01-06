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
