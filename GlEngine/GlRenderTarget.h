#pragma once

#include "IComponent.h"
#include "GraphicsContext.h"

namespace GlEngine
{
    namespace Impl
    {
        class GlRenderTargetImpl;
    }

    class Window;

    class ENGINE_SHARED GlRenderTarget : public IComponent
    {
    public:
        GlRenderTarget(Window *wnd);
        ~GlRenderTarget();

        bool Initialize();
        void Shutdown();

		void SetGraphicsContext(GraphicsContext * graphicsContext);

		void SetCurrent();
		void Flip();
		
		void Render();
		void Loop(double dt);

        inline Impl::GlRenderTargetImpl &GetImpl()
        {
            return *pimpl;
        }

    private:
        Impl::GlRenderTargetImpl *pimpl;
    };
}
