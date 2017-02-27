#include "stdafx.h"
#include "RenderTargetImpl.h"
#include "MatrixStack.h"
#include "PerspectiveViewPort.h"
#include "OrthoViewPort.h"
#include <chrono>
#include "ICamera.h"
#include "RenderPipeline.h"

namespace GlEngine::Impl
{
    RenderTargetImpl::RenderTargetImpl(RenderPipeline* pipeline)
        : _renderPipeline(pipeline), shouldRender(true), viewPorts(std::map<RenderStage*, ViewPort*>())
    {
    }
    RenderTargetImpl::~RenderTargetImpl()
    {
    }

    bool RenderTargetImpl::InitializeAsync()
    {
        return true;
    }
    void RenderTargetImpl::ShutdownAsync()
    {
    }
    bool RenderTargetImpl::InitializeGraphics()
    {
        return true;
    }
    void RenderTargetImpl::ShutdownGraphics()
    {
    }

    std::string RenderTargetImpl::name()
    {
        return "RenderTargetImpl";
    }

    void RenderTargetImpl::MakeCurrentTarget()
    {
    }

    void RenderTargetImpl::Prepare()
    {
    }
    void RenderTargetImpl::PrePush()
    {
        auto clearColor = renderPipeline() != nullptr ? renderPipeline()->clearColor() : Vector<3> { 0, 0, 0 };
        glClearColor(clearColor[0], clearColor[1], clearColor[2], 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        checkForGlError();
    }
    void RenderTargetImpl::Push(RenderStage* stage, ICamera* camera)
    {
        stage->Push();
        viewPorts[stage]->Push();
        camera->Push(stage);
    }
    void RenderTargetImpl::Pop(RenderStage* stage, ICamera* camera)
    {
        stage->Pop();
        viewPorts[stage]->Pop();
        camera->Pop(stage);
    }
    void RenderTargetImpl::PostPop()
    {
    }

    void RenderTargetImpl::Flip()
    {
    }

    RenderPipeline* RenderTargetImpl::renderPipeline()
    {
        return _renderPipeline;
    }
    void RenderTargetImpl::SetRenderPipeline(RenderPipeline* pipeline)
    {
        _renderPipeline = pipeline;
    }

    ViewPort* RenderTargetImpl::viewPort(RenderStage * stage)
    {
        return viewPorts[stage];
    }

    void RenderTargetImpl::SetViewPort(RenderStage* stage, ViewPort* viewPort)
    {
        viewPorts[stage] = viewPort;
    }
}
