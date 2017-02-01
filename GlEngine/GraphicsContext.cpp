#include "stdafx.h"
#include "GraphicsContext.h"
#include "OpenGl.h"
#include "FrameStack.h"
#include "Frame.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "ResourceLoader.h"

#include "MatrixStack.h"

namespace GlEngine
{
    GraphicsContext::GraphicsContext(Frame *frame)
        : frame(frame), frames(nullptr)
    {
        assert(frame != nullptr);
    }
    GraphicsContext::GraphicsContext(FrameStack *frames)
        : frame(nullptr), frames(frames)
    {
        assert(frames != nullptr);
    }
    GraphicsContext::~GraphicsContext()
    {
        Shutdown();
    }

    bool GraphicsContext::Initialize()
    {
        return true;
    }
    void GraphicsContext::Shutdown()
    {
    }

    rt_mutex &GraphicsContext::GetMutex()
    {
        return _mux;
    }

    const char *GraphicsContext::name()
    {
        return "GraphicsContext";
    }

    void GraphicsContext::Update(const graphics_object_map &objs, const graphics_object_map &objs_fallback)
    {
        ScopedLock _lock(_mux);

        transformed.clear();
        for (auto kv : objs)
            addTransformed(kv.first, kv.second);

        for (auto kv : objs_fallback)
        {
            bool found = false;
            for (auto oldkv : objs)
            {
                if (oldkv.first == kv.first)
                {
                    found = true;
                    break;
                }
            }
            if (found) continue;

            addTransformed(kv.first, kv.second);
        }
    }
    void GraphicsContext::addTransformed(GameObject *gobj, GraphicsObject *gfxObj)
    {
        switch (gobj->type())
        {
        case GameObjectType::Object3d:
            if (gfxObj != nullptr)
            {
                for (auto it = transformed.begin(); it != transformed.end(); it++)
                {
                    if ((*it).graphicsObject->renderOrder >= gfxObj->renderOrder)
                    {
                        transformed.insert(it, TransformedGraphicsObject(gfxObj, gobj->position, gobj->orientation));
                        return;
                    }
                }
                transformed.insert(transformed.end(), TransformedGraphicsObject(gfxObj, gobj->position, gobj->orientation));
            }
            break;

        case GameObjectType::Camera:
            UpdateCamera(gobj);
            break;

        default:
            assert(false);
        }
    }

    void GraphicsContext::UpdateCamera(GameObject *obj)
    {
        camera.SetGameObject(obj);
    }

    void GraphicsContext::AddRenderTarget(RenderTarget *renderTarget, bool queueInitialize)
    {
        ScopedLock _lock(_mux);
        assert(renderTargetCount <= MAX_RENDER_TARGETS);
        renderTargets[renderTargetCount++] = renderTarget;
        if (queueInitialize)
        {
            auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
            resources->QueueInitialize(renderTarget);
        }
    }

    void GraphicsContext::Render()
    {
        ScopedLock _lock(_mux);
        for (size_t i = 0; i < renderTargetCount; i++)
            renderTargets[i]->Prepare();

        camera.Push();
        for (size_t i = 0; i < renderTargetCount; i++)
        {
            renderTargets[i]->PrePush();
            for (auto layer = std::numeric_limits<RenderTargetLayer>::min(); layer <= std::numeric_limits<RenderTargetLayer>::max(); layer++)
            {
                if (!*renderTargets[i]) continue;
                renderTargets[i]->Push(layer);
                if (renderTargets[i]->GetShouldRender())
                {
                    for (auto it = transformed.begin(); it != transformed.end(); it++)
                        (*it).Render(layer);
                }
                renderTargets[i]->Pop(layer);
            }
            renderTargets[i]->PostPop();
        }
        camera.Pop();

        for (size_t i = 0; i < renderTargetCount; i++)
            if (renderTargets[i]->GetShouldRender())
                renderTargets[i]->Flip();
    }

    void GraphicsContext::Tick(float)
    {
        ScopedLock _lock(_mux);
        if (frames != nullptr) frames->Update(*this);
        else frame->Update(*this);
        Render();
    }
}
