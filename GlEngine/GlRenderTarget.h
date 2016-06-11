#pragma once

#include "IComponent.h"

namespace GlEngine
{
    namespace Impl
    {
        class GlRenderTargetImpl;
    }

    class Window;

    class GlRenderTarget : public IComponent
    {
    public:
        GlRenderTarget(Window *wnd);
        ~GlRenderTarget();

        bool Initialize();
        void Shutdown();

		void SetCurrent();
		void Flip();

        inline Impl::GlRenderTargetImpl &GetImpl()
        {
            return *pimpl;
        }

    private:
        Impl::GlRenderTargetImpl *pimpl;
    };
}
