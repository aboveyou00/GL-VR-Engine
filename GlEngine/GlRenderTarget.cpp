#include "stdafx.h"
#include "GlRenderTarget.h"
#include "GlRenderTargetImpl.h"

namespace GlEngine
{
    GlRenderTarget::GlRenderTarget(Window *wnd)
        : pimpl(new Impl::GlRenderTargetImpl(wnd))
    {
    }
    GlRenderTarget::~GlRenderTarget()
    {
        Shutdown();
        if (pimpl != nullptr)
        {
            delete pimpl;
            pimpl = nullptr;
        }
    }

    bool GlRenderTarget::Initialize()
    {
        return pimpl->Initialize();
    }
    void GlRenderTarget::Shutdown()
    {
        pimpl->Shutdown();
    }

	void GlRenderTarget::SetGraphicsContext(GraphicsContext * graphicsContext)
	{
		this->GetImpl().graphicsContext = graphicsContext;
	}

	void GlRenderTarget::SetCurrent()
	{
		pimpl->MakeCurrentTarget();
	}
	void GlRenderTarget::Flip()
	{
		pimpl->Flip();
	}

	void GlRenderTarget::Render()
	{
		pimpl->Render();
	}
	void GlRenderTarget::Loop(double dt)
	{
		pimpl->Loop(dt);
	}
}
