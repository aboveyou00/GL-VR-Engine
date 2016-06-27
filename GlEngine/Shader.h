#pragma once

#include "IComponent.h"

namespace GlEngine
{
    class Shader : public IComponent
    {
    public:
        Shader(const char *name);
        Shader(const char *path, const char *name);
        ~Shader();

        bool Initialize();
        void Shutdown();

        void MakeCurrent();

    private:
        const char *const _path,
                   *const _name;
        unsigned _vert, _frag, _prog;
        bool _compiled;

        unsigned compileShader(unsigned type, const char *suffix);
        bool ensureShaderCompiled(unsigned shader, const char *suffix);

        unsigned compileProgram();
        bool ensureProgramCompiled();
    };
}
