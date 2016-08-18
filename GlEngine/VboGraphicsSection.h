#pragma once

#include "GraphicsObject.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory;
    class Material;

    namespace Impl
    {
        class VboGraphicsSection
        {
        public:
            VboGraphicsSection(Material *material);
            ~VboGraphicsSection();

            void AddTriangle(Vector<3, uint16_t> indices);
            void AddQuad(Vector<4, uint16_t> indices);
            void Finalize(VboFactory<VboType::UnsignedShort, uint16_t> *face_factory);

            void Render(RenderTargetLayer layer);
            void RenderInstanced(RenderTargetLayer layer, unsigned instanceCount);

            inline Material *GetMaterial()
            {
                return material;
            }

        private:
            bool finalized;
            Material *material;
            std::vector<Vector<3, uint16_t>> *tris;
            std::vector<Vector<4, uint16_t>> *quads;
            int triCount, quadCount, triOffset, quadOffset;

            operator bool();
        };
    }
}
