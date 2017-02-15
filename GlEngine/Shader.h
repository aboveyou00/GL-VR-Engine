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

            virtual bool Initialize() override;
            virtual void Shutdown() override;
            virtual bool InitializeGraphics() override;
            virtual void ShutdownGraphics() override;

            virtual std::string name() override;

            void Push();
            void Pop();

            bool UsesVertex();
            bool UsesFragment();
            bool UsesTesselation();
            bool UsesGeometry();

            virtual operator bool() override;

            unsigned glslProgramIndex();

        private:
            ShaderSource *source;
            unsigned _prog, _vert, _tessc, _tesse, _geom, _frag;

            unsigned compileShader(unsigned type, const char *text, int text_length);
            bool ensureShaderCompiled(std::string name, unsigned shader);

            unsigned compileProgram();
            bool ensureProgramCompiled();

            void reflectShader();
            void reflectActiveAttributes();
            void reflectActiveUniforms(bool showUniformBlocks = false);
            std::string typeString(int type);
        };
    }
}
