#pragma once

#include "GraphicsObject.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory;
    class Shader;
    class Texture;

    namespace Impl
    {
        class VboGraphicsSection : GraphicsObject
        {
        public:
            VboGraphicsSection(Shader *shader, Texture *texture);
            ~VboGraphicsSection();

            void AddTriangle(Vector<3, uint16_t> indices);
            void AddQuad(Vector<4, uint16_t> indices);
            void Finalize(VboFactory<VboType::UnsignedShort, uint16_t> *face_factory);

            void PreRender() override;
            void Render() override;

            inline bool HasGraphics(Shader *shader, Texture *texture)
            {
                return this->shader == shader && this->texture == texture;
            }
            inline Shader *GetShader()
            {
                return shader;
            }
            inline Texture *GetTexture()
            {
                return texture;
            }

        private:
            bool finalized;
            Shader *shader;
            Texture *texture;
            std::vector<Vector<3, uint16_t>> *tris;
            std::vector<Vector<4, uint16_t>> *quads;
            int triCount, quadCount, triOffset, quadOffset;

            virtual const char *name() override;
            virtual operator bool() override;
        };
    }
}
