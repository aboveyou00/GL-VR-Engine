#pragma once

#include "EngineShared.h"
#include "GraphicsObject.h"
#include "Vector.h"
#include "Matrix.h"

namespace GlEngine
{
	namespace Impl
	{
		class TransformedGraphicsObjectImpl;
	}

	class ENGINE_SHARED TransformedGraphicsObject 
	{
	public:
		TransformedGraphicsObject() : TransformedGraphicsObject(nullptr) {}
		TransformedGraphicsObject(GraphicsObject * obj);
		TransformedGraphicsObject(GraphicsObject & obj);
		TransformedGraphicsObject(GraphicsObject * obj, Vector<3> position, Matrix<4, 4> orientation);
		TransformedGraphicsObject(GraphicsObject & obj, Vector<3> position, Matrix<4, 4> orientation);
		~TransformedGraphicsObject();

		void Render() const;

	private:
		Impl::TransformedGraphicsObjectImpl * pimpl;
	};
}