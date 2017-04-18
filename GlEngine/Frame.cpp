#include "stdafx.h"
#include "Frame.h"
#include "GameObject.h"
#include "Event.h"
#include "CameraComponent.h"
#include "RenderTarget.h"
#include "SimpleRenderPipeline.h"

namespace GlEngine
{
    Frame::Frame()
        : _initialized(false), currentCamera(nullptr), _mainCamera(nullptr), _mainPipeline(nullptr), spatialPartitions(nullptr)
    {
    }
    Frame::~Frame()
    {
        SafeDelete(spatialPartitions);
    }

    std::string Frame::name()
    {
        return "Frame";
    }

    bool Frame::Initialize()
    {
        if (_initialized) return true;
        _initialized = true;
        return true;
    }
    void Frame::Shutdown()
    {
        if (!_initialized) return;
        _initialized = false;
    }

    void Frame::Tick(float delta)
    {
        for (size_t q = 0; q < _children.size(); q++)
        {
            if (_children[q]->active()) _children[q]->Tick(delta);
        }
    }

    void Frame::HandleEvent(Events::Event &evt)
    {
        if (evt.IsHandled()) return;
        for (size_t q = 0; q < _children.size(); q++)
        {
            if (!_children[q]->active()) continue;
            _children[q]->HandleEvent(evt);
            if (evt.IsHandled()) return;
        }
    }

    void Frame::TickGraphics(float delta)
    {
        for (size_t q = 0; q < _children.size(); q++)
        {
            if (!_children[q]->active()) continue;
            _children[q]->TickGraphics(delta);
        }
    }
    void Frame::UpdateGraphics()
    {
        for (size_t q = 0; q < _children.size(); q++)
        {
            if (!_children[q]->active()) continue;
            _children[q]->UpdateGraphics();
        }
    }
    void Frame::Render(RenderStage* stage)
    {
        for (size_t q = 0; q < _children.size(); q++)
        {
            if (!_children[q]->active()) continue;
            _children[q]->Render(stage);
        }
    }

    void Frame::FramePushed(FrameStack&)
    {
    }
    void Frame::FramePopped(FrameStack&)
    {
    }
    void Frame::FrameMasked(FrameStack&)
    {
    }
    void Frame::FrameUnmasked(FrameStack&)
    {
    }

    GameObject *Frame::findChild(std::string name)
    {
        for (size_t q = 0; q < _children.size(); q++)
        {
            if (_children[q]->name().compare(name) == 0)
            {
                return _children[q];
            }
            //TODO: check the child's children recursively
        }
        return nullptr;
    }

    std::vector<GameObject*> Frame::children()
    {
        return _children;
    }

    ICamera *Frame::mainCamera()
    {
        return _mainCamera;
    }

    RenderPipeline *Frame::mainPipeline()
    {
        return _mainPipeline;
    }

    std::vector<std::pair<RenderStage*, ICamera*>> Frame::renderStages()
    {
        if (_mainPipeline == nullptr) CreateDefaultPipeline();
        return _mainPipeline->renderStages();
    }

    Vector<3> Frame::clearColor()
    {
        if (_mainPipeline == nullptr) return { 0, 0, 0 };
        return _mainPipeline->clearColor();
    }
    void Frame::SetClearColor(Vector<3> color)
    {
        assert(false);
    }

    RenderPipeline* Frame::CreateDefaultPipeline()
    {
        CameraComponent *camera;
        return CreateDefaultPipeline(camera);
    }
    RenderPipeline* Frame::CreateDefaultPipeline(CameraComponent*& cameraComponent)
    {
        cameraComponent = new CameraComponent();
        auto ccgobj = new GameObject(this, "MainCamera");
        ccgobj->AddComponent(cameraComponent);
        SetMainCamera(cameraComponent);

        auto pipeline = new SimpleRenderPipeline(this, { { renderStage_opaque, cameraComponent },{ renderStage_translucent, cameraComponent },{ renderStage_2d, cameraComponent } });
        SetMainPipeline(pipeline);
        return pipeline;
    }

    void Frame::SetMainCamera(ICamera* camera)
    {
        _mainCamera = camera;
    }

    void Frame::SetMainPipeline(RenderPipeline* pipeline)
    {
        _mainPipeline = pipeline;
    }

    void Frame::setCurrentRenderTarget(RenderTarget *target)
    {
        currentRenderTarget = target;
    }
    void Frame::setCurrentCamera(ICamera *camera)
    {
        currentCamera = camera;
    }
    Frame * Frame::frame()
    {
        return this;
    }
}
