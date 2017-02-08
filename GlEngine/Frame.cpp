#include "stdafx.h"
#include "Frame.h"
#include "GameObject.h"
#include "CameraGameObject.h"
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
        if (initialized) return true;
        initialized = true;
        for (size_t q = 0; q < objects.size(); q++)
        {
            if (!objects[q]->Initialize()) return false;
        }
        return true;
    }
    void Frame::Shutdown()
    {
        if (!initialized) return;
        initialized = false;
        for (size_t q = 0; q < objects.size(); q++)
            objects[q]->Shutdown();
    }
    void Frame::Tick(float delta)
    {
        for (size_t q = 0; q < objects.size(); q++)
            if (objects[q]->active() && objects[q]->requiresTick())
                objects[q]->Tick(delta);
    }

    std::string Frame::name()
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
            auto unique = obj->requiresUniqueGraphics();
            auto &map_to_use = unique ? map : gobj_map;
            auto idx = map_to_use.find(obj);
            if (idx == map_to_use.end())
            {
                map_to_use[obj] = obj->CreateGraphicsObject(unique ? nullptr : &ctx);
                //if (initialized) obj->Initialize(); //TODO: Why is this here?
            }
            else if (obj->requiresGraphicsTick() && !unique)
            {
                obj->UpdateGraphicsObject(&ctx, idx->second);
                //TODO: get this working for game objects that require unique graphics also
            }
        }

        ctx.Update(map, gobj_map);
    }
    
    void Frame::HandleEvent(Events::Event &evt)
    {
        if (evt.IsHandled()) return;
        for (size_t q = 0; q < objects.size(); q++)
        {
            if (!objects[q]->active()) continue;
            objects[q]->HandleEvent(evt);
            if (evt.IsHandled()) return;
        }
    }
}
