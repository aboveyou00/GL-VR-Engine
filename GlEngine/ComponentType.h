#pragma once
#include <numeric>

namespace GlEngine::ShaderFactory
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

    ENGINE_SHARED std::ostream &operator<<(std::ostream &stream, ComponentType type);
}

CONTIGUOUS_ENUM_H(GlEngine::ShaderFactory::ComponentType, Input, Output)
