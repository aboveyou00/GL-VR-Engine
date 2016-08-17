#pragma once

#include "IComponent.h"
#include "RenderTarget.h"

namespace GlEngine
{
	class Window;

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
