#include "stdafx.h"
#include "Image2dMaterial.h"
#include "Texture.h"
#include "Shader.h"

namespace GlEngine
{
    Image2dMaterial::Image2dMaterial()
        : Material(true)//,
          //singleShader(GlEngine::Shader::Create("Shaders", "tex_2d"))
    {
    }
    Image2dMaterial::~Image2dMaterial()
    {
    }

    void Image2dMaterial::SetTexture(Texture *tex)
    {
        this->tex = tex;
    }

    void Image2dMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory;
        assert(false);
        //assert(!instanced);
        //if (singleShader && *singleShader) singleShader->Push();
        //if (tex && *tex) tex->Push();
    }
    //void Image2dMaterial::Pop(bool instanced)
    //{
    //    assert(!instanced);
    //    if (tex && *tex) tex->Pop();
    //    assert(false);
    //    //if (singleShader && *singleShader) singleShader->Pop();
    //}

    bool Image2dMaterial::IsOpaque()
    {
        return !tex || tex->IsOpaque();
    }
    TesselationType Image2dMaterial::GetTesselationType()
    {
        return GlEngine::TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> Image2dMaterial::properties()
    {
        return { };
    }
    std::vector<ShaderFactory::Attribute*> Image2dMaterial::attributes()
    {
        return { };
    }

    const char *Image2dMaterial::name()
    {
        return "Image2dMaterial";
    }
    Image2dMaterial::operator bool()
    {
        assert(false);
        return tex && *tex;// && singleShader && *singleShader;
    }
}
