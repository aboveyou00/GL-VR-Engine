#pragma once

#include "IComponent.h"
#include "RenderTarget.h"

namespace GlEngine
{
	namespace Impl
	{
		class RenderTargetImpl;
	}

	class Window;

	class ENGINE_SHARED WindowRenderTarget : public RenderTarget
	{
	public:
		WindowRenderTarget(Window * window);
		~WindowRenderTarget();
	};
}
