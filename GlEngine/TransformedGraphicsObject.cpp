#include "stdafx.h"
#include "TransformedGraphicsObject.h"
#include "OpenGl.h"

namespace GlEngine
{
    TransformedGraphicsObject::TransformedGraphicsObject()
        : TransformedGraphicsObject(nullptr)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject & obj, Vector<3> position, Matrix<4, 4> orientation)
        : TransformedGraphicsObject(&obj, position, orientation)
    {
    }
	TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject * obj, Vector<3> position, Matrix<4, 4> orientation)
        : graphicsObject(obj), position(position), orientation(orientation)
	{
	}
	TransformedGraphicsObject::~TransformedGraphicsObject()
	{
	}

	void TransformedGraphicsObject::Render() const
	{
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
        glMultMatrixf(Matrix<4, 4>::TranslateMatrix(position).getAddr());
        glMultMatrixf(orientation.getAddr());

		static bool init = false;
		if (!init++)
			graphicsObject->Initialize();
        graphicsObject->Render();

        glPopMatrix();
	}
}
