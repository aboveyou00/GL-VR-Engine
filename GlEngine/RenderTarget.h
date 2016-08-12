#pragma once

#include "IComponent.h"
#include "Camera.h"

namespace GlEngine
{
	class ViewPort;

    namespace Impl
    {
        class RenderTargetImpl;
    }

    class Window;

	class ENGINE_SHARED RenderTarget : public IComponent
    {
    public:
		RenderTarget(Impl::RenderTargetImpl *impl);
		~RenderTarget();

		bool Initialize();
		void Shutdown();

		const char *name();
		void SetViewPort(ViewPort * viewPort);

		void SetCurrent();

		bool GetShouldRender();

		void Prepare();
		void Push();
		void Pop();

		void Flip();

        inline Impl::RenderTargetImpl &GetImpl()
        {
            return *pimpl;
        }

    protected:
		Impl::RenderTargetImpl *pimpl;
    };
}
