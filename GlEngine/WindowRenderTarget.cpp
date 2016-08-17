#include "stdafx.h"
#include "WindowRenderTarget.h"
#include "WindowRenderTargetImpl.h"

namespace GlEngine
{
	WindowRenderTarget::WindowRenderTarget(Window * window)
	{
		pimpl = new Impl::WindowRenderTargetImpl(window);
	}
	WindowRenderTarget::~WindowRenderTarget()
	{
	}
}