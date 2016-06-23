#pragma once

#include "Vector.h"
#include "Matrix.h"
#include "GraphicsObject.h"

namespace GlEngine
{
	namespace Impl
	{
		class TransformedGraphicsObjectImpl
		{
		public:
			TransformedGraphicsObjectImpl(GraphicsObject* graphicsObject) : graphicsObject(graphicsObject) {}
			TransformedGraphicsObjectImpl(GraphicsObject& graphicsObject) : graphicsObject(&graphicsObject) {}
			TransformedGraphicsObjectImpl(GraphicsObject* graphicsObject, Vector<3> position, Matrix<4, 4> orientation) : graphicsObject(graphicsObject), position(position), orientation(orientation) {}
			TransformedGraphicsObjectImpl(GraphicsObject& graphicsObject, Vector<3> position, Matrix<4, 4> orientation) : graphicsObject(&graphicsObject), position(position), orientation(orientation) {}
			~TransformedGraphicsObjectImpl() {}

			GraphicsObject * graphicsObject;

			void Render() const;

			Vector<3> position;
			Matrix<4, 4> orientation = Matrix<4, 4>::Identity();
		};
	}
}