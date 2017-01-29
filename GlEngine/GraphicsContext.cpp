#include "stdafx.h"
#include "GraphicsContext.h"
#include "OpenGl.h"
#include "FrameStack.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "ResourceLoader.h"

#include "MatrixStack.h"

namespace GlEngine
{
    GraphicsContext::GraphicsContext(FrameStack *frames)
        : frames(frames)
    {
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

    void GraphicsContext::Update(const graphics_object_map &objs)
    {
        ScopedLock _lock(_mux);

        transformed.clear();
        for (auto kv : objs)
        {
            if (kv.first->type() == GameObjectType::Object3d)
            {
                if (kv.second != nullptr)
                {
                    for (auto it = transformed.begin(); it != transformed.end(); it++)
                    {
                        if ((*it).graphicsObject->renderOrder >= kv.second->renderOrder)
                        {
                            transformed.insert(it, TransformedGraphicsObject(kv.second, kv.first->position, kv.first->orientation));
                            goto inserted;
                        }
                    }
                    transformed.insert(transformed.end(), TransformedGraphicsObject(kv.second, kv.first->position, kv.first->orientation));
                    inserted:;
                }
            }
            else if (kv.first->type() == GameObjectType::Camera)
                UpdateCamera(kv.first);
        }
    }

    void GraphicsContext::UpdateCamera(GameObject *obj)
    {
        camera.SetGameObject(obj);
    }

    void GraphicsContext::AddRenderTarget(RenderTarget *renderTarget)
    {
        ScopedLock _lock(_mux);
        assert(renderTargetCount <= MAX_RENDER_TARGETS);
        renderTargets[renderTargetCount++] = renderTarget;
        auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources->QueueInitialize(renderTarget);
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
        }
        camera.Pop();

        for (size_t i = 0; i < renderTargetCount; i++)
            if (renderTargets[i]->GetShouldRender())
                renderTargets[i]->Flip();
    }

    void GraphicsContext::Tick(float)
    {
        ScopedLock _lock(_mux);
        frames->Update(*this);
        Render();
    }
}
