#pragma once

#include "IComponent.h"
#include "IGraphicsComponent.h"
#include "Attribute.h"

namespace GlEngine
{
    class ENGINE_SHARED Shader : public IGraphicsComponent
    {
    public:
        Shader();
        Shader(std::vector<ShaderFactory::Attribute>, std::string vert_src = "", std::string frag_src = "", std::string tessc_src = "", std::string tesse_src = "", std::string geom_src = "");
        ~Shader();

        inline static Shader *Create(const char *shader_name)
        {
            return Create("", shader_name);
        }
        static Shader *Create(const char *shader_path, const char *shader_name);
        //static Shader * Create(ShaderAttribs attribs);

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
        ShaderFactory::Program program;
        unsigned _vert, _frag, _tessc, _tesse, _geom, _prog;

        unsigned compileShader(unsigned type, const char *text, int text_length);
        bool ensureShaderCompiled(unsigned shader);

        unsigned compileProgram();
        bool ensureProgramCompiled();
    };
}
