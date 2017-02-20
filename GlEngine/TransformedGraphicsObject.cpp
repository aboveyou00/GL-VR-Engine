#include "stdafx.h"
#include "TransformedGraphicsObject.h"
#include "OpenGl.h"
#include "MatrixStack.h"
#include <sstream>

namespace GlEngine
{
    TransformedGraphicsObject::TransformedGraphicsObject()
        : TransformedGraphicsObject(nullptr)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject *obj, Transform transform)
        : TransformedGraphicsObject(obj, transform.position, transform.orientation)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject &obj, Transform transform)
        : TransformedGraphicsObject(&obj, transform.position, transform.orientation)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject &obj, Matrix<4, 4> transformation)
        : TransformedGraphicsObject(&obj, transformation)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject *obj, Matrix<4, 4> transformation)
        : GraphicsObject(false), graphicsObject(obj), transformation(transformation)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject &obj, Vector<3> position, Matrix<4, 4> orientation)
        : TransformedGraphicsObject(&obj, position, orientation)
    {
    }
    TransformedGraphicsObject::TransformedGraphicsObject(GraphicsObject *obj, Vector<3> position, Matrix<4, 4> orientation)
        : TransformedGraphicsObject(obj, orientation * Mat3T<float>::TranslateMatrix(position))
    {
    }
    TransformedGraphicsObject::~TransformedGraphicsObject()
    {
    }

    std::string TransformedGraphicsObject::name()
    {
        std::stringstream stream;
        stream << "Transformed<" << graphicsObject->name() << ">";
        return stream.str();
    }
    bool TransformedGraphicsObject::isReady()
    {
        return graphicsObject && graphicsObject->isReady();
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
        MatrixStack::Model.mult(transformation);
    }
    void TransformedGraphicsObject::RenderImpl(RenderTargetLayer layer)
    {
        if (isReady()) graphicsObject->Render(layer);
    }
    void TransformedGraphicsObject::PostRender(RenderTargetLayer)
    {
        MatrixStack::Model.pop();
    }
}
