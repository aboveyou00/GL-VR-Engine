#include "stdafx.h"
#include "Frame.h"
#include "GameObject.h"
#include "GraphicsContext.h"
#include "Event.h"

namespace GlEngine
{
    Frame::Frame()
        : initialized(false)
    {
    }
    Frame::~Frame()
    {
    }

    bool Frame::Initialize()
    {
        for (size_t q = 0; q < objects.size(); q++)
        {
            if (!objects[q]->Initialize()) return false;
        }
        initialized = true;
        return true;
    }
    void Frame::Shutdown()
    {
        if (!initialized) return;
        for (size_t q = 0; q < objects.size(); q++)
        {
            objects[q]->Shutdown();
        }
    }
    void Frame::Tick(float delta)
    {
        for (size_t q = 0; q < objects.size(); q++)
            if (objects[q]->RequiresTick())
            {
                objects[q]->Tick(delta);
            }
    }

    const char *Frame::name()
    {
        return "Frame";
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

    void Frame::DestroyGameObject(GameObject *gobj)
    {
        auto idx = std::find(objects.begin(), objects.end(), gobj);
        if (idx != objects.end())
        {
            objects.erase(idx);
            gobj->RemoveFromFrame(this);
            if (initialized) gobj->Shutdown();
            delete gobj;
        }
    }
    bool Frame::OwnsGameObject(GameObject *gobj)
    {
        auto idx = std::find(objects.begin(), objects.end(), gobj);
        return idx != objects.end();
    }

    void Frame::Update(GraphicsContext &ctx)
    {
        auto &map = this->context_map[&ctx];
        for (size_t q = 0; q < objects.size(); q++)
        {
            auto obj = objects[q];
            if (map.find(obj) == map.end()) map[obj] = obj->CreateGraphicsObject(ctx);
        }
        ctx.Update(map);
    }
    
    void Frame::HandleEvent(Events::Event &evt)
    {
        if (evt.IsHandled()) return;
        for (size_t q = 0; q < objects.size(); q++)
        {
            objects[q]->HandleEvent(evt);
            if (evt.IsHandled()) return;
        }
    }
}
