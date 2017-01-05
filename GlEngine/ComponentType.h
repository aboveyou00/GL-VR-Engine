#pragma once
#include <limits>

namespace GlEngine
{
    namespace ShaderFactory
    {
        enum class ENGINE_SHARED ComponentType : unsigned
        {
            Vertex = 0,
            TessControl = 1,
            TessEvaluation = 2,
            Geometry = 3,
            Fragment = 4,
            Pseudo = 5
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
            return T::Vertex;
        }
        static constexpr T max() noexcept
        {
            return T::Pseudo;
        }
    };
}
