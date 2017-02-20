#include "stdafx.h"
#include "WindowRenderTarget.h"
#include "WindowRenderTargetImpl.h"

namespace GlEngine
{
    WindowRenderTarget::WindowRenderTarget(Window *window, CameraComponent *camera)
        : RenderTarget(new Impl::WindowRenderTargetImpl(window, camera))
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
