#pragma once

#include "IComponent.h"
#include "Camera.h"
#include "RenderTargeLayer.h"

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
		RenderTarget();
		~RenderTarget();

		virtual bool Initialize();
		virtual void Shutdown();

		virtual const char *name();
		void SetViewPort(RenderTargetLayer layer, ViewPort * viewPort);

		void SetCurrent();

		virtual bool GetShouldRender();

		virtual void Prepare();
		virtual void Push(RenderTargetLayer layer);
		virtual void Pop(RenderTargetLayer layer);

		virtual void Flip();

        inline Impl::RenderTargetImpl &GetImpl()
        {
            return *pimpl;
        }

    protected:
		Impl::RenderTargetImpl *pimpl;
    };
}
