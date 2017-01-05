#pragma once
#include <limits>

namespace GlEngine
{
    namespace ShaderFactory
    {
        enum class ENGINE_SHARED ComponentType : unsigned
        {
            Input = 0,
            Vertex,
            TessControl,
            TessEvaluation,
            Geometry,
            Fragment,
            Output
        };
    }
}

namespace std
{
    template <>
    class numeric_limits<GlEngine::ShaderFactory::ComponentType>
    {
        typedef GlEngine::ShaderFactory::ComponentType T;

    public:
        static constexpr T min() noexcept
        {
            return T::Input;
        }
        static constexpr T max() noexcept
        {
            return T::Output;
        }
    };
}
