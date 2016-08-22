#pragma once

#include "IComponent.h"
#include "IGraphicsComponent.h"

namespace GlEngine
{
    class ENGINE_SHARED ShaderFactory : public IGraphicsComponent
    {
    public:
        ShaderFactory();
		ShaderFactory(std::string vert_src = "", std::string frag_src = "", std::string tessc_src = "", std::string tesse_src = "", std::string geom_src = "");
        ~ShaderFactory();

        inline static ShaderFactory *Create(const char *shader_name)
        {
            return Create("", shader_name);
        }
        static ShaderFactory *Create(const char *shader_path, const char *shader_name);
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
        std::string vert_src, frag_src, tessc_src, tesse_src, geom_src;
        unsigned _vert, _frag, _tessc, _tesse, _geom, _prog;

        unsigned compileShader(unsigned type, const char *text, int text_length);
        bool ensureShaderCompiled(unsigned shader);

        unsigned compileProgram();
        bool ensureProgramCompiled();
    };
}
