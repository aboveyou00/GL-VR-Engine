#include "stdafx.h"
#include "WaterMaterial.h"
#include "Texture.h"
#include "Shader.h"
#include "Property.h"

namespace TileRPG
{
    WaterMaterial *WaterMaterial::GetInstance()
    {
        static WaterMaterial *instance = nullptr;
        if (instance == nullptr) instance = new WaterMaterial();
        return instance;
    }
    
    WaterMaterial::WaterMaterial()
        : texture(GlEngine::Texture::FromFile("Textures/water.png", GlEngine::TextureFlag::Translucent))//, shader(GlEngine::ShaderFactory::Create("Shaders", "water"))
    {
    }
    WaterMaterial::~WaterMaterial()
    {
    }

    void WaterMaterial::Push(GlEngine::ShaderFactory::ShaderFactory &factory)
    {
        factory;
    }

    std::vector<GlEngine::ShaderFactory::ShaderProp*> WaterMaterial::properties()
    {
        return {
            &GlEngine::ShaderFactory::prop_Texture
        };
    }
    std::vector<GlEngine::ShaderFactory::Attribute*> WaterMaterial::attributes()
    {
        return { };
    }

    //void WaterMaterial::Push(bool instanced)
    //{
    //    instanced;
    //    //assert(!instanced);
    //    //if (shader && *shader) shader->Push();
    //    //texture->Push();
    //}
    //void WaterMaterial::Pop(bool instanced)
    //{
    //    instanced;
    //    //assert(!instanced);
    //    //texture->Pop();
    //    //if (shader && *shader) shader->Pop();
    //}

    bool WaterMaterial::IsOpaque()
    {
        return texture->IsOpaque();
    }
    GlEngine::TesselationType WaterMaterial::GetTesselationType()
    {
        return GlEngine::TesselationType::Triangles;
    }

    std::string WaterMaterial::name()
    {
        return "WaterMaterial";
    }
    WaterMaterial::operator bool()
    {
        return texture && *texture;
    }
}
