#include "stdafx.h"
#include "MathUtils.h"

namespace GlEngine
{
    namespace Util
    {        
        constexpr double radToDeg(const double rad)
        {
            return rad / PI * 180;
        }
        constexpr double degToRad(const double deg)
        {
            return deg * PI / 180;
        }
    }
}

double operator "" rad(long double angle)
{
    return static_cast<double>(angle);
}
double operator "" deg(unsigned long long angle)
{
    return GlEngine::Util::degToRad((float)angle);
}
double operator "" deg(long double angle)
{
    return GlEngine::Util::degToRad((float)angle);
}