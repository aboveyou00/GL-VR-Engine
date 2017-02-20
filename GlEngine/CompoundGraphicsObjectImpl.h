#pragma once

#include "GraphicsObject.h"
#include "TransformedGraphicsObject.h"

namespace GlEngine
{
    namespace Impl
    {
        class ENGINE_SHARED CompoundGraphicsObjectImpl : public GraphicsObject
        {
        public:
            CompoundGraphicsObjectImpl(TransformedGraphicsObject *t_gobjs, unsigned count);
            ~CompoundGraphicsObjectImpl();

            void BuildVao(VaoFactory &vao) override;

            void RenderImpl(RenderTargetLayer layer) override;
            void RenderInstancedImpl(RenderTargetLayer layer, unsigned instanceCount) override;

            virtual std::string name() override;

            virtual bool isReady() override;

            TransformedGraphicsObject &operator[](unsigned idx);
            const TransformedGraphicsObject &operator[](unsigned idx) const;

        private:
            TransformedGraphicsObject *t_gobjs;
            unsigned count;
        };
    }
}
