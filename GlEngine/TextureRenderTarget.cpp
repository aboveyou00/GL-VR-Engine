#include "stdafx.h"
#include "TextureRenderTarget.h"
#include "TextureRenderTargetImpl.h"

namespace GlEngine
{
    TextureRenderTarget::TextureRenderTarget(unsigned width, unsigned height)
        : RenderTarget(new Impl::TextureRenderTargetImpl(width, height))
    {
    }
    TextureRenderTarget::~TextureRenderTarget()
    {
    }
    const char *TextureRenderTarget::name()
    {
        return "TextureRenderTarget";
    }
}
