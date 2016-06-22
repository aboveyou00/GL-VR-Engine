#include "stdafx.h"
#include "TransformedGraphicsObject.h"
#include "TransformedGraphicsObjectImpl.h"

namespace GlEngine
{
	TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject & obj)
		: pimpl(new Impl::TransformedGraphicsObjectImpl(obj))
	{
	}
	TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject * obj)
		: pimpl(new Impl::TransformedGraphicsObjectImpl(obj))
	{
	}
	TransformedGraphicsObject::~TransformedGraphicsObject()
	{
		if (pimpl != nullptr)
		{
			delete pimpl;
			pimpl = nullptr;
		}
	}

	void TransformedGraphicsObject::Render()
	{
		pimpl->Render();
	}
}