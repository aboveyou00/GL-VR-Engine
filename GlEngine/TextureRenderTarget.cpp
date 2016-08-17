#include "stdafx.h"
#include "TextureRenderTarget.h"
#include "TextureRenderTargetImpl.h"

namespace GlEngine
{
	TextureRenderTarget::TextureRenderTarget(unsigned width, unsigned height, bool hasAlphaChannel)
	{
		pimpl = new Impl::TextureRenderTargetImpl(width, height, hasAlphaChannel);
	}
	TextureRenderTarget::~TextureRenderTarget()
	{
	}
}