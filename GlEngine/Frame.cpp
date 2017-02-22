#include "stdafx.h"
#include "Frame.h"
#include "GameObject.h"
#include "Event.h"
#include "CameraComponent.h"
#include "RenderTarget.h"

namespace GlEngine
{
    Frame::Frame()
        : _initialized(false), currentCamera(nullptr)
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

    void Frame::setCurrentRenderTarget(RenderTarget *target)
    {
        currentRenderTarget = target;
        if (target == nullptr) setCurrentCamera(nullptr);
        else setCurrentCamera(target->camera());
    }
    void Frame::setCurrentCamera(CameraComponent *camera)
    {
        if (currentCamera != nullptr) currentCamera->Pop();
        else currentCamera = camera;
        if (currentCamera != nullptr) currentCamera->Push();
    }
}
