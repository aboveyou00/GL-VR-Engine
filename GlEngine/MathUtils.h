#pragma once

namespace GlEngine
{
	namespace Util
	{
		constexpr extern double PI = 3.1415926535897932;

        ENGINE_SHARED constexpr float radToDeg(const float rad);
        ENGINE_SHARED constexpr float degToRad(const float deg);
        ENGINE_SHARED constexpr double radToDeg_d(const double rad);
        ENGINE_SHARED constexpr double degToRad_d(const double deg);
		ENGINE_SHARED inline int floor_int(double flt)
		{
			return (int)flt - (flt < 0);
		}
		ENGINE_SHARED inline int ceil_int(double flt)
		{
			return -(floor_int(-flt));
		}
	}
}

ENGINE_SHARED float operator "" rad(long double angle);
ENGINE_SHARED float operator "" deg(unsigned long long angle);
ENGINE_SHARED float operator "" deg(long double angle);

ENGINE_SHARED double operator "" rad_d(long double angle);
ENGINE_SHARED double operator "" deg_d(unsigned long long angle);
ENGINE_SHARED double operator "" deg_d(long double angle);
