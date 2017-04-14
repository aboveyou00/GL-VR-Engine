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

            void AddLine(Vector<2, uint16_t> indices);
            void AddTriangle(Vector<3, uint16_t> indices);
            void AddQuad(Vector<4, uint16_t> indices);
            void Finalize(VboFactory<VboType::UnsignedShort, uint16_t> *face_factory);

            void Render(RenderStage* stage);
            void RenderInstanced(RenderStage* stage, unsigned instanceCount);

            void RenderPoints(RenderStage* stage, unsigned count);

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
            std::vector<Vector<2, uint16_t>> *lines;
            std::vector<Vector<3, uint16_t>> *tris;
            std::vector<Vector<4, uint16_t>> *quads;
            int lineCount, triCount, quadCount, lineOffset, triOffset, quadOffset;

            ShaderFactory::ShaderFactory *_factory;
        };
    }
}
