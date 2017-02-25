#include "stdafx.h"
#include "RenderTarget.h"
#include "RenderTargetImpl.h"
#include "ICamera.h"
#include "Frame.h"

#include "Engine.h"
#include "GraphicsController.h"

namespace GlEngine
{
    RenderTarget::RenderTarget(Impl::RenderTargetImpl *pimpl)
        : pimpl(pimpl),
          _viewMode(RenderTargetViewMode::Relative),
          _viewMatrix(Matrix<4, 4>::Identity())
    {
    }
    RenderTarget::~RenderTarget()
    {
        //TODO: Don't call this here!
        ShutdownAsync();
        if (pimpl != nullptr)
        {
            delete pimpl;
            pimpl = nullptr;
        }
    }

    bool RenderTarget::InitializeAsync()
    {
        return pimpl->InitializeAsync();
    }
    void RenderTarget::ShutdownAsync()
    {
        pimpl->ShutdownAsync();
    }
    bool RenderTarget::InitializeGraphics()
    {
        return pimpl->InitializeGraphics();
    }
    void RenderTarget::ShutdownGraphics()
    {
        pimpl->ShutdownGraphics();
    }

    std::string RenderTarget::name()
    {
        return "RenderTarget";
    }

    bool RenderTarget::isReady()
    {
        return pimpl->isReady();
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

    void RenderTarget::Render()
    {
        auto thisCamera = camera();
        Frame *thisFrame = nullptr;
        if (thisCamera != nullptr) thisFrame = camera()->frame();

        if (thisFrame == nullptr || !GetShouldRender()) return;

        thisFrame->setCurrentRenderTarget(this);

        thisFrame->UpdateGraphics();

        this->PrePush();
        for (auto layer = std::numeric_limits<RenderTargetLayer>::min(); layer <= std::numeric_limits<RenderTargetLayer>::max(); layer++)
        {
            this->Push(layer);
            //thisCamera->Push();
            thisFrame->Render(layer);
            //thisCamera->Pop();
            this->Pop(layer);
        }
        this->PostPop();

        thisFrame->setCurrentRenderTarget(nullptr);
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

    void RenderTarget::AddToGraphicsLoop()
    {
        Engine::GetInstance().GetGraphicsController().addRenderTarget(this);
    }

    ICamera *RenderTarget::camera()
    {
        return pimpl->camera();
    }
    void RenderTarget::SetCamera(ICamera *camera)
    {
        pimpl->SetCamera(camera);
    }
}
