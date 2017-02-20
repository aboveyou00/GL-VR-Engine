#pragma once

#include "IAsyncInitializable.h"
#include "ComponentArray.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Shader : public IAsyncInitializable
        {
        private:
            Shader(ShaderSource *source);
            ~Shader();

        public:
            static Shader *Create(ShaderSource *source);

            virtual bool InitializeAsync() override;
            virtual void ShutdownAsync() override;
            virtual bool InitializeGraphics() override;
            virtual void ShutdownGraphics() override;

            virtual bool isReady() override;

            virtual std::string name() override;

            void Push();
            void Pop();

            bool UsesVertex();
            bool UsesFragment();
            bool UsesTesselation();
            bool UsesGeometry();

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
