#pragma once

#include "GraphicsObject.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory;
    class Material;
    
    namespace ShaderFactory
    {
        class ShaderFactory;
        class IPropertyProvider;
    }
    
    namespace Impl
    {
        class ENGINE_SHARED VboGraphicsSection
        {
        public:
            VboGraphicsSection(Material *material, std::vector<ShaderFactory::IPropertyProvider*> &providers, ShaderFactory::ShaderFactory* factory = nullptr);
            ~VboGraphicsSection();

            void AddTriangle(Vector<3, uint16_t> indices);
            void AddQuad(Vector<4, uint16_t> indices);
            void Finalize(VboFactory<VboType::UnsignedShort, uint16_t> *face_factory);

            void Render(RenderTargetLayer layer);
            void RenderInstanced(RenderTargetLayer layer, unsigned instanceCount);

            void RenderPoints(RenderTargetLayer layer, unsigned count);

            inline Material *GetMaterial()
            {
                return material;
            }

            ShaderFactory::ShaderFactory &factory();
            void SetFactory(ShaderFactory::ShaderFactory* factory, std::vector<ShaderFactory::IPropertyProvider*> &providers);

            operator bool();

        private:
            bool finalized;
            Material *material;
            std::vector<Vector<3, uint16_t>> *tris;
            std::vector<Vector<4, uint16_t>> *quads;
            int triCount, quadCount, triOffset, quadOffset;

            ShaderFactory::ShaderFactory *_factory;
        };
    }
}
