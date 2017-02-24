#include "stdafx.h"
#include "Frame.h"
#include "GameObject.h"
#include "Event.h"
#include "CameraComponent.h"
#include "RenderTarget.h"

namespace GlEngine
{
    Frame::Frame()
        : _initialized(false), currentCamera(nullptr), _mainCamera(nullptr)
    {
    }
    Frame::~Frame()
    {
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
    void Frame::Render(RenderTargetLayer layer)
    {
        for (size_t q = 0; q < _children.size(); q++)
        {
            if (!_children[q]->active()) continue;
            _children[q]->Render(layer);
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

    void Frame::Push()
    {
        if (_mainCamera == nullptr) return;
        _mainCamera->Push();
    }
    void Frame::Pop()
    {
        if (_mainCamera == nullptr) return;
        _mainCamera->Pop();
    }

    Vector<3> Frame::clearColor()
    {
        if (_mainCamera == nullptr) return ICamera::clearColor();
        return _mainCamera->clearColor();
    }

    bool Frame::isReady()
    {
        if (_mainCamera == nullptr) return false;
        return _mainCamera->isReady();
    }

    ICamera *Frame::mainCamera()
    {
        return _mainCamera;
    }

    CameraComponent *Frame::CreateDefaultCamera()
    {
        auto cc = new CameraComponent();
        auto ccgobj = new GameObject(this, "MainCamera");
        ccgobj->AddComponent(cc);
        SetMainCamera(cc);
        return cc;
    }
    void Frame::SetMainCamera(ICamera *camera)
    {
        _mainCamera = camera;
    }

    void Frame::setCurrentRenderTarget(RenderTarget *target)
    {
        currentRenderTarget = target;
        if (target == nullptr) setCurrentCamera(nullptr);
        else setCurrentCamera(target->camera());
    }
    void Frame::setCurrentCamera(ICamera *camera)
    {
        if (currentCamera != nullptr) currentCamera->Pop();
        else currentCamera = camera;
        if (currentCamera != nullptr) currentCamera->Push();
    }

    Frame *Frame::frame()
    {
        return this;
    }
}
