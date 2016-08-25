#include "stdafx.h"
#include "RenderTargetLayer.h"

GlEngine::RenderTargetLayer operator++(GlEngine::RenderTargetLayer &ref, int) noexcept
{
    auto oldval = ref;
    if (ref == std::numeric_limits<GlEngine::RenderTargetLayer>::max()) ref = std::numeric_limits<GlEngine::RenderTargetLayer>::min();
    else ref = static_cast<GlEngine::RenderTargetLayer>(static_cast<int>(ref) + 1);
    return oldval;
}
GlEngine::RenderTargetLayer operator--(GlEngine::RenderTargetLayer &ref, int) noexcept
{
    auto oldval = ref;
    if (ref == std::numeric_limits<GlEngine::RenderTargetLayer>::min()) ref = std::numeric_limits<GlEngine::RenderTargetLayer>::max();
    else ref = static_cast<GlEngine::RenderTargetLayer>(static_cast<int>(ref) - 1);
    return oldval;
}
GlEngine::RenderTargetLayer operator++(GlEngine::RenderTargetLayer &ref) noexcept
{
    if (ref == std::numeric_limits<GlEngine::RenderTargetLayer>::max()) ref = std::numeric_limits<GlEngine::RenderTargetLayer>::min();
    else ref = static_cast<GlEngine::RenderTargetLayer>(static_cast<int>(ref) + 1);
    return ref;
}
GlEngine::RenderTargetLayer operator--(GlEngine::RenderTargetLayer &ref) noexcept
{
    if (ref == std::numeric_limits<GlEngine::RenderTargetLayer>::min()) ref = std::numeric_limits<GlEngine::RenderTargetLayer>::max();
    else ref = static_cast<GlEngine::RenderTargetLayer>(static_cast<int>(ref) - 1);
    return ref;
}
