#pragma once

#include "RenderTarget.h"
#include "Window.h"

namespace GlEngine
{
	namespace Impl
	{
		class WindowRenderTargetImpl;
	}

	class WindowRenderTarget : public RenderTarget
	{
		WindowRenderTarget(Window * window);
		~WindowRenderTarget();
	};
}