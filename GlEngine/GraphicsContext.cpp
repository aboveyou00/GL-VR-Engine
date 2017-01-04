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
        : frames(frames),
          _loop(
            [&] { return this->InitializeRenderTargets(); },
            [&](float delta) { this->Tick(delta); },
            [&] { this->ShutdownRenderTargets(); }
          )
    {
    }
    GraphicsContext::~GraphicsContext()
    {
        Shutdown();
    }

    bool GraphicsContext::Initialize()
    {
        _loop.RunLoop();
        return true;
    }
    void GraphicsContext::Shutdown()
    {
        _loop.StopLoop(false);
    }

    const char *GraphicsContext::name()
    {
        return "GraphicsContext";
    }

    void GraphicsContext::Update(const graphics_object_map &objs)
    {
        ScopedLock slock(_lock);

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

    void GraphicsContext::UpdateCamera(GameObject* obj)
    {
        camera.SetGameObject(obj);
    }

    void GraphicsContext::AddRenderTarget(RenderTarget * renderTarget)
    {
        renderTargets[renderTargetCount++] = renderTarget;
    }

    void GraphicsContext::Render()
    {
        {
            ScopedLock _lock(GlEngine::Engine::GetInstance().GetMutex());
            for (size_t i = 0; i < renderTargetCount; i++)
                renderTargets[i]->Prepare();
        }

        camera.Push();
        for (size_t i = 0; i < renderTargetCount; i++)
        {
            renderTargets[i]->PrePush();
            for (int layer_int = (int)std::numeric_limits<RenderTargetLayer>::min(); layer_int < (int)std::numeric_limits<RenderTargetLayer>::max() + 1; layer_int++)
            {
                renderTargets[i]->Push((RenderTargetLayer)layer_int);
                if (renderTargets[i]->GetShouldRender())
                {
                    for (auto it = transformed.begin(); it != transformed.end(); it++)
                        (*it).Render((RenderTargetLayer)layer_int);
                }
                renderTargets[i]->Pop((RenderTargetLayer)layer_int);
            }
        }
        camera.Pop();

        for (size_t i = 0; i < renderTargetCount; i++)
            if (renderTargets[i]->GetShouldRender())
                renderTargets[i]->Flip();
    }

    bool GraphicsContext::InitializeRenderTargets()
    {
        this_thread_name() = "graphics";
        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "Beginning OpenGL graphics thread");
        for (size_t q = 0; q < renderTargetCount; q++)
            if (!renderTargets[q]->Initialize()) return false;
        return true;
    }
    void GraphicsContext::Tick(float)
    {
        auto &resources = *Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources.InitializeResourceGraphics();

        frames->Update(*this);
        Render();
    }
    void GraphicsContext::ShutdownRenderTargets()
    {
        auto &resources = *Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
        resources.ShutdownResourceGraphics();

        auto logger = GlEngine::Engine::GetInstance().GetServiceProvider().GetService<GlEngine::ILogger>();
        logger->Log(GlEngine::LogType::Info, "Terminating OpenGL graphics thread");
        for (size_t q = 0; q < renderTargetCount; q++)
            renderTargets[q]->Shutdown();
    }
}
