#pragma once

#include "IComponent.h"
#include "Camera.h"

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

		Camera * GetCamera();
		void SetCamera(Camera * cam);

		void SetCurrent();
		void Flip();
		
		void Push();
		void Pop();

        inline Impl::GlRenderTargetImpl &GetImpl()
        {
            return *pimpl;
        }

    private:
        Impl::GlRenderTargetImpl *pimpl;
    };
}
