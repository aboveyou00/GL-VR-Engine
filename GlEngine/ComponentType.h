#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        enum class ENGINE_SHARED ComponentType
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
