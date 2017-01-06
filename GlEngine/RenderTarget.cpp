#include "stdafx.h"
#include "RenderTarget.h"
#include "RenderTargetImpl.h"

#include "RenderTargetImpl.h"

namespace GlEngine
{
    RenderTarget::RenderTarget(Impl::RenderTargetImpl *pimpl)
        : pimpl(pimpl)
    {
    }
    RenderTarget::~RenderTarget()
    {
        Shutdown();
        if (pimpl != nullptr)
        {
            delete pimpl;
            pimpl = nullptr;
        }
    }

    bool RenderTarget::Initialize()
    {
        return pimpl->Initialize();
    }
    void RenderTarget::Shutdown()
    {
        pimpl->Shutdown();
    }

    const char *RenderTarget::name()
    {
        return "GlRenderTarget";
    }
    void RenderTarget::SetViewPort(RenderTargetLayer layer, ViewPort * viewPort)
    {
        pimpl->SetViewPort(layer, viewPort);
    }

    void RenderTarget::SetCurrent()
    {
        pimpl->MakeCurrentTarget();
    }

    bool RenderTarget::GetShouldRender()
    {
        return pimpl->GetShouldRender();
    }

    void RenderTarget::Prepare()
    {
        pimpl->Prepare();
    }
    void RenderTarget::PrePush()
    {
        pimpl->PrePush();
    }
    void RenderTarget::Push(RenderTargetLayer layer)
    {
        pimpl->Push(layer);
    }
    void RenderTarget::Pop(RenderTargetLayer layer)
    {
        pimpl->Pop(layer);
    }

    void RenderTarget::Flip()
    {
        pimpl->Flip();
    }
}
