#include "stdafx.h"
#include "RenderTarget.h"
#include "RenderTargetImpl.h"
#include "PerspectiveViewPort.h"
#include "OrthoViewPort.h"

namespace GlEngine
{
    RenderTarget::RenderTarget(Impl::RenderTargetImpl *pimpl)
        : pimpl(pimpl)
    {
        auto viewport3d = new PerspectiveViewPort();
        auto viewport2d = new OrthoViewPort();
        SetViewPort(GlEngine::RenderTargetLayer::Layer3dOpaque, viewport3d);
        SetViewPort(GlEngine::RenderTargetLayer::Layer3dTransluscent, viewport3d);
        SetViewPort(GlEngine::RenderTargetLayer::Layer2d, viewport2d);
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
    bool RenderTarget::InitializeGraphics()
    {
        return pimpl->InitializeGraphics();
    }
    void RenderTarget::ShutdownGraphics()
    {
        pimpl->ShutdownGraphics();
    }

    const char *RenderTarget::name()
    {
        return "RenderTarget";
    }
    void RenderTarget::SetViewPort(RenderTargetLayer layer, ViewPort * viewPort)
    {
        pimpl->SetViewPort(layer, viewPort);
    }
    ViewPort *RenderTarget::viewPort(RenderTargetLayer layer)
    {
        return pimpl->viewPort(layer);
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

    RenderTarget::operator bool()
    {
        return !!*pimpl;
    }
}
