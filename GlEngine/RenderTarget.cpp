#include "stdafx.h"
#include "RenderTarget.h"
#include "RenderTargetImpl.h"

namespace GlEngine
{
    RenderTarget::RenderTarget(Impl::RenderTargetImpl *pimpl)
        : pimpl(pimpl), _viewMode(RenderTargetViewMode::Relative), _viewMatrix(Matrix<4, 4>::Identity())
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
        pimpl->Push(layer, _viewMode, _viewMatrix);
    }
    void RenderTarget::Pop(RenderTargetLayer layer)
    {
        pimpl->Pop(layer);
    }
    void RenderTarget::PostPop()
    {
        pimpl->PostPop();
    }

    void RenderTarget::Flip()
    {
        pimpl->Flip();
    }

    RenderTargetViewMode RenderTarget::viewMode()
    {
        return _viewMode;
    }
    void RenderTarget::SetViewMode(RenderTargetViewMode mode)
    {
        _viewMode = mode;
    }

    Matrix<4, 4> RenderTarget::viewMatrix()
    {
        return _viewMatrix;
    }
    void RenderTarget::SetViewMatrix(Matrix<4, 4> mat)
    {
        _viewMatrix = mat;
    }

    RenderTarget::operator bool()
    {
        return !!*pimpl;
    }
}
