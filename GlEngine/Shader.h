#pragma once

#include "IGraphicsComponent.h"
#include "ComponentArray.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Shader : public IGraphicsComponent
        {
        private:
            Shader(ShaderSource *source);
            ~Shader();

        public:
            static Shader *Create(ShaderSource *source);

            bool Initialize() override;
            void Shutdown() override;
            bool InitializeGraphics() override;
            void ShutdownGraphics() override;

            const char *name() override;

            void Push();
            void Pop();

            bool UsesVertex();
            bool UsesFragment();
            bool UsesTesselation();
            bool UsesGeometry();

            operator bool();

        private:
            ShaderSource *source;
            unsigned _prog, _vert, _tessc, _tesse, _geom, _frag;

            unsigned compileShader(unsigned type, const char *text, int text_length);
            bool ensureShaderCompiled(unsigned shader);

            unsigned compileProgram();
            bool ensureProgramCompiled();
        };
    }
}
