#pragma once

#include <numeric>

namespace GlEngine
{
	enum class RenderTargetLayer
	{
		Layer3dOpaque = 0,
		Layer3dTransluscent = 1,
		Layer2d = 2,
	};
}

template<>
constexpr GlEngine::RenderTargetLayer std::numeric_limits<GlEngine::RenderTargetLayer>::min() noexcept
{
    return GlEngine::RenderTargetLayer::Layer3dOpaque;
}
template<>
constexpr GlEngine::RenderTargetLayer std::numeric_limits<GlEngine::RenderTargetLayer>::max() noexcept
{
    return GlEngine::RenderTargetLayer::Layer2d;
}

GlEngine::RenderTargetLayer ENGINE_SHARED operator++(GlEngine::RenderTargetLayer &ref, int) noexcept;
GlEngine::RenderTargetLayer ENGINE_SHARED operator--(GlEngine::RenderTargetLayer &ref, int) noexcept;
GlEngine::RenderTargetLayer ENGINE_SHARED operator++(GlEngine::RenderTargetLayer &ref) noexcept;
GlEngine::RenderTargetLayer ENGINE_SHARED operator--(GlEngine::RenderTargetLayer &ref) noexcept;
