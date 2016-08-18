#include "stdafx.h"
#include "TransformedGraphicsObject.h"
#include "OpenGl.h"
#include "MatrixStack.h"

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

	void TransformedGraphicsObject::Render(RenderTargetLayer layer) const
	{
        if (graphicsObject)
        {
            MatrixStack::ModelView.mult(Mat3T<float>::TranslateMatrix(position) * orientation);
            graphicsObject->Render(layer);
            MatrixStack::ModelView.pop();
        }
	}
}
