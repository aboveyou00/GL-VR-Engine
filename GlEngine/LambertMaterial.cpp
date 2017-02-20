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
        : Material("LambertMaterial"), texture(texture)//, instancedShader(nullptr), singleShader(nullptr)
    {
    }
    LambertMaterial::~LambertMaterial()
    {
    }

    void LambertMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory;
        assert(false);
        //auto shader = instanced ? instancedShader : singleShader;
        //if (shader && *shader) shader->Push();
        //texture->Push();
    }
    //void LambertMaterial::Pop(bool instanced)
    //{
    //    instanced;
    //    texture->Pop();
    //    //auto shader = instanced ? instancedShader : singleShader;
    //    //if (shader && *shader) shader->Pop();
    //}

    bool LambertMaterial::IsOpaque()
    {
        return texture->IsOpaque();
    }
    
    TesselationType LambertMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> LambertMaterial::properties()
    {
        return { };
    }
    std::vector<ShaderFactory::Attribute*> LambertMaterial::attributes()
    {
        return { };
    }

    std::string LambertMaterial::name()
    {
        return "LambertMaterial";
    }

    bool LambertMaterial::isReady()
    {
        return texture && texture->isReady();// && instancedShader && *instancedShader && singleShader && *singleShader;
    }
}
