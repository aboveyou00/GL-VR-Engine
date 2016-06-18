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

	void GraphicsObject::Render()
	{
		pimpl->Render();
	}
}