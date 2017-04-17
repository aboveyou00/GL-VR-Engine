#pragma once

#include "GraphicsObject.h"
#include "vbo_element_t.h"

namespace GlEngine
{
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

            void AddLine(Vector<2, array_index_t> indices);
            void AddTriangle(Vector<3, array_index_t> indices);
            void AddQuad(Vector<4, array_index_t> indices);
            void Finalize(VboFactory<ElementVboFactoryVboType, array_index_t> *face_factory);

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
            std::vector<Vector<2, array_index_t>> *lines;
            std::vector<Vector<3, array_index_t>> *tris;
            std::vector<Vector<4, array_index_t>> *quads;
            int lineCount, triCount, quadCount, lineOffset, triOffset, quadOffset;

            ShaderFactory::ShaderFactory *_factory;
        };
    }
}
