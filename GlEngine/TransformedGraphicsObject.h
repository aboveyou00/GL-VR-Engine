#pragma once

#include "GraphicsObject.h"
#include "Vector.h"
#include "Matrix.h"

namespace GlEngine
{
	class ENGINE_SHARED TransformedGraphicsObject 
	{
	public:
        TransformedGraphicsObject();
		TransformedGraphicsObject(GraphicsObject & obj, Vector<3> position = Vector<3> { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
		TransformedGraphicsObject(GraphicsObject * obj, Vector<3> position = Vector<3> { 0, 0, 0 }, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
		~TransformedGraphicsObject();

        void Render() const;

        GraphicsObject * graphicsObject;

        Vector<3> position;
        Matrix<4, 4> orientation;
	};
}
