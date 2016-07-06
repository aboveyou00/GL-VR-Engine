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

	Camera * GlRenderTarget::GetCamera()
	{
		return pimpl->camera;
	}

	void GlRenderTarget::SetCamera(Camera * cam)
	{
		pimpl->camera = cam;
	}

	void GlRenderTarget::SetCurrent()
	{
		pimpl->MakeCurrentTarget();
	}

    bool GlRenderTarget::GetShouldRender()
    {
        return pimpl->GetShouldRender();
    }

    void GlRenderTarget::Prepare()
    {
        pimpl->Prepare();
    }
    void GlRenderTarget::Push()
	{
		pimpl->Push();
	}
	void GlRenderTarget::Pop()
	{
		pimpl->Pop();
	}

	void GlRenderTarget::Flip()
	{
		pimpl->Flip();
	}
}
