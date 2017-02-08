#pragma once

#include "GraphicsObject.h"

namespace GlEngine
{
    class ENGINE_SHARED EmptyGraphicsObject : public GraphicsObject
    {
    public:
        EmptyGraphicsObject();
        ~EmptyGraphicsObject();
        
        std::string name() override;
        operator bool() override;

        void BuildVao(VaoFactory & vao) override;
        void RenderInstancedImpl(RenderTargetLayer layer, unsigned instanceCount) override;

        void RenderImpl(RenderTargetLayer layer) override;
    };
}
