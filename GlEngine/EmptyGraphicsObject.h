#pragma once

#include "GraphicsObject.h"

namespace GlEngine
{
    class ENGINE_SHARED EmptyGraphicsObject : public GraphicsObject
    {
    public:
        EmptyGraphicsObject();
        ~EmptyGraphicsObject();

        virtual bool isReady() override;

        void BuildVao(VaoFactory &vao) override;
        void RenderInstancedImpl(RenderStage* stage, unsigned instanceCount) override;

        void RenderImpl(RenderStage* stage) override;
    };
}
