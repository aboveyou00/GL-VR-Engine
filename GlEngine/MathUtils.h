#pragma once

namespace GlEngine
{
    namespace Util
    {
        constexpr extern double PI = 3.1415926535897932;
        constexpr extern float PI_f = 3.14159265f;

        ENGINE_SHARED constexpr float radToDeg(const float rad);
        ENGINE_SHARED constexpr float degToRad(const float deg);
        ENGINE_SHARED constexpr double radToDeg_d(const double rad);
        ENGINE_SHARED constexpr double degToRad_d(const double deg);
        ENGINE_SHARED inline int floor_int(double flt)
        {
            return flt > 0 ? (int)(floor(flt)) : (int)(-ceil(-flt));
        }
        ENGINE_SHARED inline int ceil_int(double flt)
        {
            return flt > 0 ? (int)(ceil(flt)) : (int)(-floor(-flt));
        }
        
        ENGINE_SHARED bool triangleRayIntersection(Vector<3> t1, Vector<3> t2, Vector<3> t3, Vector<3> rayOrigin, Vector<3> rayDirection, float* outDistance = nullptr);
        ENGINE_SHARED bool triangleAABBIntersection(Vector<3> t1, Vector<3> t2, Vector<3> t3, Vector<3> topLeftBack, Vector<3> size);
        ENGINE_SHARED bool pointInTriangle2d(Vector<2> point, Vector<2> t1, Vector<2> t2, Vector<2> t3);
    }
}

ENGINE_SHARED float operator "" rad(long double angle);
ENGINE_SHARED float operator "" deg(unsigned long long angle);
ENGINE_SHARED float operator "" deg(long double angle);

ENGINE_SHARED double operator "" rad_d(long double angle);
ENGINE_SHARED double operator "" deg_d(unsigned long long angle);
ENGINE_SHARED double operator "" deg_d(long double angle);
