#pragma once

namespace GlEngine::ShaderFactory
{
    enum class PropertyResolutionEagerness
    {
        Unset,
        Earliest,
        Default,
        Latest
    };
}