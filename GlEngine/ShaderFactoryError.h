#pragma once

namespace GlEngine::ShaderFactory
{
    enum class ShaderFactoryError : unsigned
    {
        None = 0,
        AttributeDependencyError
    };
}
