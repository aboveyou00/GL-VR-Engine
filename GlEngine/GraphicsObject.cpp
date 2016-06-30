#include "stdafx.h"
#include "GraphicsObject.h"
#include "GraphicsObjectImpl.h"

namespace GlEngine
{
	GraphicsObject::GraphicsObject()
		: pimpl(new Impl::GraphicsObjectImpl())
	{
	}
	GraphicsObject::~GraphicsObject()
	{
		if (pimpl != nullptr)
		{
			delete pimpl;
			pimpl = nullptr;
		}
	}

    bool GraphicsObject::Initialize()
    {
        return pimpl->Initialize();
    }
    void GraphicsObject::Shutdown()
    {
        pimpl->Shutdown();
    }

	void GraphicsObject::Render()
	{
		pimpl->Render();
	}
}
