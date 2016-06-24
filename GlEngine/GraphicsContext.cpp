#include "stdafx.h"
#include "GraphicsContext.h"
#include "OpenGl.h"

namespace GlEngine
{
    GraphicsContext::GraphicsContext()
        : _loop([&] { this_thread_name() = "graphics"; return this->InitializeRenderTargets(); }, [&](float delta) { this->Tick(delta); }, [&] { this->ShutdownRenderTargets(); })
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

	void GraphicsContext::Register(GameObject * gameObject, GraphicsObject * graphicsObject)
	{
		ScopedLock slock(_lock);

		objs[gameObject] = graphicsObject;
	}

	void GraphicsContext::UnRegister(GameObject * gameObject)
	{
		ScopedLock slock(_lock);

		objs[gameObject] = nullptr;
	}

	void GraphicsContext::Update()
	{
		ScopedLock slock(_lock);

		transformedCount = 0;
		for (auto kv : objs)
			transformed[transformedCount++] = TransformedGraphicsObject(kv.second, kv.first->position, kv.first->orientation);
	}

	void GraphicsContext::AddRenderTarget(GlRenderTarget * renderTarget)
	{
		renderTargets[renderTargetCount++] = renderTarget;
	}

	void GraphicsContext::Render()
	{
		camera.Push();
		for (size_t i = 0; i < renderTargetCount; i++)
		{
			renderTargets[i]->Push();
			for (int j = 0; j < transformedCount; j++)
				transformed[j].Render();
			renderTargets[i]->Pop();
		}
		camera.Pop();

		for (size_t i = 0; i < renderTargetCount; i++)
			renderTargets[i]->Flip();
	}

    bool GraphicsContext::InitializeRenderTargets()
    {
        for (size_t q = 0; q < renderTargetCount; q++)
            if (!renderTargets[q]->Initialize()) return false;
        return true;
    }
    void GraphicsContext::Tick(float)
    {
        Update();
        Render();
    }
    void GraphicsContext::ShutdownRenderTargets()
    {
        for (size_t q = 0; q < renderTargetCount; q++)
            renderTargets[q]->Shutdown();
    }
}
