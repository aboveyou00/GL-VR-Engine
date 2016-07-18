#include "stdafx.h"
#include "GraphicsContext.h"
#include "OpenGl.h"
#include "FrameStack.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ILogger.h"
#include "ResourceLoader.h"

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
		camera.SetEye({ 0, 0, 20 });
		camera.SetTarget({ 0, 0, 0 });

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

		transformedCount = 0;
		for (auto kv : objs)
            if (kv.second != nullptr)
                transformed[transformedCount++] = TransformedGraphicsObject(kv.second, kv.first->position, kv.first->orientation);
	}

	void GraphicsContext::AddRenderTarget(GlRenderTarget * renderTarget)
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
			renderTargets[i]->Push();
            if (renderTargets[i]->GetShouldRender())
            {
			    for (int j = 0; j < transformedCount; j++)
				    transformed[j].Render();
            }
			renderTargets[i]->Pop();
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
