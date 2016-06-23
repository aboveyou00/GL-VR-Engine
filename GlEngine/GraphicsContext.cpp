#include "stdafx.h"
#include "GraphicsContext.h"
#include "OpenGl.h"

namespace GlEngine
{
	GraphicsContext::GraphicsContext() {}
	GraphicsContext::~GraphicsContext() {}

	bool GraphicsContext::Initialize()
	{
		return true;
	}

	void GraphicsContext::Shutdown()
	{
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
		for (int i = 0; i < renderTargetCount; i++)
		{
			renderTargets[i]->Push();
			for (int j = 0; j < transformedCount; j++)
				transformed[j].Render();
			renderTargets[i]->Pop();
		}
		camera.Pop();

		for (int i = 0; i < renderTargetCount; i++)
			renderTargets[i]->Flip();
	}
}