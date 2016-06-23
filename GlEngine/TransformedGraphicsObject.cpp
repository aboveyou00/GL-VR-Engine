#include "stdafx.h"
#include "TransformedGraphicsObject.h"
#include "TransformedGraphicsObjectImpl.h"

namespace GlEngine
{
	TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject * obj)
		: pimpl(new Impl::TransformedGraphicsObjectImpl(obj))
	{
	}
	TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject & obj)
		: pimpl(new Impl::TransformedGraphicsObjectImpl(obj))
	{
	}
	TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject * obj, Vector<3> position, Matrix<4, 4> orientation)
		: pimpl(new Impl::TransformedGraphicsObjectImpl(obj, position, orientation))
	{
	}
	TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject & obj, Vector<3> position, Matrix<4, 4> orientation)
		: pimpl(new Impl::TransformedGraphicsObjectImpl(obj, position, orientation))
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

	void TransformedGraphicsObject::Render() const
	{
		pimpl->Render();
	}
}