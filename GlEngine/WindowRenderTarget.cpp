#include "stdafx.h"
#include "WindowRenderTarget.h"
#include "WindowRenderTargetImpl.h"

namespace GlEngine
{
    WindowRenderTarget::WindowRenderTarget(Window *window)
        : RenderTarget(new Impl::WindowRenderTargetImpl(window))
    {
    }
    WindowRenderTarget::~WindowRenderTarget()
    {
    }

    std::string WindowRenderTarget::name()
    {
        return "WindowRenderTarget";
    }
}
