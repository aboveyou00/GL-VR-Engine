#pragma once

#include "IComponent.h"
#include "IGraphicsComponent.h"

namespace GlEngine
{
    class Shader : public IGraphicsComponent
    {
    public:
        Shader();
        Shader(const char *name);
        Shader(const char *path, const char *name);
        ~Shader();

        inline static Shader *Create(const char *shader_name)
        {
            return Create("", shader_name);
        }
        static Shader *Create(const char *shader_path, const char *shader_name);

        bool Initialize() override;
        void Shutdown() override;
        bool InitializeGraphics() override;
        void ShutdownGraphics() override;

        const char *name() override;

        void MakeCurrent();

        operator bool();

    private:
        const char *_path, *_name;
        
        const char *_vert_text, *_frag_text;
        int _vert_text_length, _frag_text_length;

        unsigned _vert, _frag, _prog;

        bool loadShaderText(const char *&text, int &text_length, const char *suffix);

        unsigned compileShader(unsigned type, const char *text, int text_length);
        bool ensureShaderCompiled(unsigned shader, const char *suffix);

        unsigned compileProgram();
        bool ensureProgramCompiled();
    };
}
