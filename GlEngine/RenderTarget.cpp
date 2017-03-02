#include "stdafx.h"
#include "RenderTarget.h"
#include "RenderTargetImpl.h"
#include "ICamera.h"
#include "Frame.h"

#include "Engine.h"
#include "GraphicsController.h"
#include "RenderPipeline.h"

namespace GlEngine
{
    RenderTarget::RenderTarget(Impl::RenderTargetImpl *pimpl)
        : pimpl(pimpl)
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

    RenderPipeline * RenderTarget::renderPipeline()
    {
        return pimpl->renderPipeline();
    }
    void RenderTarget::SetRenderPipeline(RenderPipeline * pipeline)
    {
        pimpl->SetRenderPipeline(pipeline);
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
        if (!GetShouldRender()) return;

        RenderPipeline* thisPipeline = renderPipeline();
        Frame* thisFrame = nullptr;
        
        if (thisPipeline != nullptr)
            thisFrame = thisPipeline->frame();
        if (thisFrame == nullptr)
            return;

        thisFrame->setCurrentRenderTarget(this);
        thisFrame->UpdateGraphics();

        this->PrePush();
        for (auto stageCameraPair : renderPipeline()->renderStages())
        {
            this->Push(stageCameraPair.first, stageCameraPair.second);
            thisFrame->Render(stageCameraPair.first);
            this->Pop(stageCameraPair.first, stageCameraPair.second);
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
    void RenderTarget::Push(RenderStage* stage, ICamera* camera)
    {
        pimpl->Push(stage, camera);
    }
    void RenderTarget::Pop(RenderStage* stage, ICamera* camera)
    {
        pimpl->Pop(stage, camera);
    }
    void RenderTarget::PostPop()
    {
        pimpl->PostPop();
    }

    void RenderTarget::Flip()
    {
        pimpl->Flip();
    }

    void RenderTarget::AddToGraphicsLoop()
    {
        Engine::GetInstance().GetGraphicsController().addRenderTarget(this);
    }

    ViewPort * RenderTarget::viewPort(RenderStage * stage)
    {
        return pimpl->viewPort(stage);
    }
    void RenderTarget::SetViewPort(RenderStage * stage, ViewPort * viewPort)
    {
        pimpl->SetViewPort(stage, viewPort);
    }
}
