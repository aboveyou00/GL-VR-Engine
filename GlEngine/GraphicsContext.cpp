#include "stdafx.h"
#include "GraphicsContext.h"
#include "GraphicsContextImpl.h"

namespace GlEngine
{
	GraphicsContext::GraphicsContext() 
		: pimpl(new Impl::GraphicsContextImpl())
	{
	}
	GraphicsContext::~GraphicsContext() 
	{
		Shutdown();
		if (pimpl != nullptr)
		{
			delete pimpl;
			pimpl = nullptr;
		}
	}
	
	bool GraphicsContext::Initialize()
	{
		return pimpl->Initialize();
	}

	void GraphicsContext::Shutdown()
	{
		pimpl->Shutdown();
	}

	void GraphicsContext::AddGraphicsObject(TransformedGraphicsObject * graphicsObject)
	{
		pimpl->AddGraphicsObject(graphicsObject);
	}

	void GraphicsContext::RemoveGraphicsObject(TransformedGraphicsObject * graphicsObject)
	{
		pimpl->RemoveGraphicsObject(graphicsObject);
	}

	void GraphicsContext::Render()
	{
		pimpl->Render();
	}
}