#include "stdafx.h"
#include "BlinnMaterial.h"
#include "Texture.h"
#include "Shader.h"

namespace GlEngine
{
    BlinnMaterial *BlinnMaterial::Create(Texture *texture)
    {
        static std::vector<BlinnMaterial*> cache;
        for (auto ptr = cache.begin(); ptr != cache.end(); ptr++)
        {
            auto &mat = **ptr;
            if (mat.texture == texture) return &mat;
        }

        auto blinn = new BlinnMaterial(texture);
        cache.push_back(blinn);
        return blinn;
    }

    BlinnMaterial::BlinnMaterial(Texture *texture)
        : texture(texture), instancedShader(ShaderFactory::Create("Shaders", "direct_light_tex.inst")), singleShader(ShaderFactory::Create("Shaders", "direct_light_tex"))
    {
    }
    BlinnMaterial::~BlinnMaterial()
    {
    }

    void BlinnMaterial::Push(bool instanced)
    {
        auto shader = instanced ? instancedShader : singleShader;
        if (shader && *shader) shader->Push();
        texture->Push();
    }
    void BlinnMaterial::Pop(bool instanced)
    {
        texture->Pop();
        auto shader = instanced ? instancedShader : singleShader;
        if (shader && *shader) shader->Pop();
    }

    bool BlinnMaterial::IsOpaque()
    {
        return texture->IsOpaque();
    }
	
    TesselationType BlinnMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    const char *BlinnMaterial::name()
    {
        return "BlinnMaterial";
    }
    BlinnMaterial::operator bool()
    {
        return texture && *texture && instancedShader && *instancedShader && singleShader && *singleShader;
    }
}
