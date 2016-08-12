#pragma once

#include "RenderTarget.h"
#include "Window.h"

namespace GlEngine
{
	namespace Impl
	{
		class WindowRenderTargetImpl;
	}

	class ENGINE_SHARED WindowRenderTarget : public RenderTarget
	{
    public:
		WindowRenderTarget(Window * window);
		~WindowRenderTarget();
	};
}
