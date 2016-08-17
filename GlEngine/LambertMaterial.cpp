#include "stdafx.h"
#include "LambertMaterial.h"
#include "Texture.h"
#include "Shader.h"

namespace GlEngine
{
    LambertMaterial *LambertMaterial::Create(Texture *texture)
    {
        static std::vector<LambertMaterial*> cache;
        for (auto ptr = cache.begin(); ptr != cache.end(); ptr++)
        {
            auto &mat = **ptr;
            if (mat.texture == texture) return &mat;
        }

        auto lambert = new LambertMaterial(texture);
        cache.push_back(lambert);
        return lambert;
    }

    LambertMaterial::LambertMaterial(Texture *texture)
        : texture(texture), instancedShader(nullptr), singleShader(nullptr)
    {
    }
    LambertMaterial::~LambertMaterial()
    {
    }

    void LambertMaterial::Push(bool instanced)
    {
        auto shader = instanced ? instancedShader : singleShader;
        if (shader && *shader) shader->Push();
        texture->Push();
    }
    void LambertMaterial::Pop(bool instanced)
    {
        texture->Pop();
        auto shader = instanced ? instancedShader : singleShader;
        if (shader && *shader) shader->Pop();
    }

    bool LambertMaterial::IsOpaque()
    {
        return texture->IsOpaque();
    }
    TesselationType LambertMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    const char *LambertMaterial::name()
    {
        return "LambertMaterial";
    }
    LambertMaterial::operator bool()
    {
        return texture && *texture && instancedShader && *instancedShader && singleShader && *singleShader;
    }
}
