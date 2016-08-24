#pragma once

namespace GlEngine
{
    namespace Util
    {
        template <typename T>
        inline T random()
        {
            return random<T>(T(1));
        }
        template <typename T>
        inline T random(T t);

        template <>
        inline float ENGINE_SHARED random<float>(float t);
        template <>
        inline double ENGINE_SHARED random<double>(double t);
        template <>
        inline unsigned ENGINE_SHARED random<unsigned>(unsigned t);
        template <>
        inline int ENGINE_SHARED random<int>(int t);
    }
}
