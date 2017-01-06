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
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject & obj, Matrix<4, 4> transformation)
        : TransformedGraphicsObject(&obj, transformation)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject * obj, Matrix<4, 4> transformation)
        : GraphicsObject(false), graphicsObject(obj), transformation(transformation)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject & obj, Vector<3> position, Matrix<4, 4> orientation)
        : TransformedGraphicsObject(&obj, position, orientation)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject * obj, Vector<3> position, Matrix<4, 4> orientation)
        : TransformedGraphicsObject(obj, Mat3T<float>::TranslateMatrix(position) * orientation)
    {
    }
    TransformedGraphicsObject::~TransformedGraphicsObject()
    {
    }

    const char *TransformedGraphicsObject::name()
    {
        return "TransformedGraphicsObject";
    }
    TransformedGraphicsObject::operator bool()
    {
        return graphicsObject && *graphicsObject;
    }

    void TransformedGraphicsObject::BuildVao(VaoFactory&)
    {
        assert(false);
    }
    void TransformedGraphicsObject::RenderInstancedImpl(RenderTargetLayer, unsigned)
    {
        assert(false);
    }

    void TransformedGraphicsObject::PreRender(RenderTargetLayer)
    {
        MatrixStack::ModelView.mult(transformation);
    }
    void TransformedGraphicsObject::RenderImpl(RenderTargetLayer layer)
    {
        if (graphicsObject && *graphicsObject) graphicsObject->Render(layer);
    }
    void TransformedGraphicsObject::PostRender(RenderTargetLayer)
    {
        MatrixStack::ModelView.pop();
    }
}
