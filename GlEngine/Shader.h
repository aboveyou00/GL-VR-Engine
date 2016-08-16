#pragma once

#include "IComponent.h"
#include "IGraphicsComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED Shader : public IGraphicsComponent
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

        void Push();
        void Pop();

        bool UsesTesselation();

        operator bool();

    private:
        const char *_path, *_name;
        float theta;
        
        const char *_vert_text, *_frag_text, *_tessc_text, *_tesse_text;
        int _vert_text_length, _frag_text_length, _tessc_text_length, _tesse_text_length;

        unsigned _vert, _frag, _tessc, _tesse, _prog;

        bool loadShaderText(const char *&text, int &text_length, const char *suffix, bool required = true);

        unsigned compileShader(unsigned type, const char *text, int text_length);
        bool ensureShaderCompiled(unsigned shader, const char *suffix);

        unsigned compileProgram();
        bool ensureProgramCompiled();
    };
}
