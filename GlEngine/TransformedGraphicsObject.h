#pragma once

#include "GraphicsObject.h"
#include "Vector.h"
#include "Matrix.h"

namespace GlEngine
{
    class ENGINE_SHARED TransformedGraphicsObject : public GraphicsObject
    {
    public:
        TransformedGraphicsObject();
        TransformedGraphicsObject(GraphicsObject &obj, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        TransformedGraphicsObject(GraphicsObject *obj, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        TransformedGraphicsObject(GraphicsObject &obj, Vector<3> position, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        TransformedGraphicsObject(GraphicsObject *obj, Vector<3> position, Matrix<4, 4> orientation = Matrix<4, 4>::Identity());
        ~TransformedGraphicsObject();

        std::string name() override;
        operator bool() override;

        void BuildVao(VaoFactory &vao) override;
        void RenderInstancedImpl(RenderTargetLayer layer, unsigned instanceCount) override;

        void PreRender(RenderTargetLayer layer) override;
        void RenderImpl(RenderTargetLayer layer) override;
        void PostRender(RenderTargetLayer layer) override;

        GraphicsObject *graphicsObject;
        Matrix<4, 4> transformation;
    };
}
