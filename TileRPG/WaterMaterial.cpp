#include "stdafx.h"
#include "WaterMaterial.h"
#include "Texture.h"
#include "Shader.h"

namespace TileRPG
{
    WaterMaterial *WaterMaterial::GetInstance()
    {
        static WaterMaterial *instance = nullptr;
        if (instance == nullptr) instance = new WaterMaterial();
        return instance;
    }
    
    WaterMaterial::WaterMaterial()
        : texture(GlEngine::Texture::FromFile("Textures/water.png", true)), shader(GlEngine::Shader::Create("Shaders", "water"))
    {
    }
    WaterMaterial::~WaterMaterial()
    {
    }

    void WaterMaterial::Push(bool instanced)
    {
        assert(!instanced);
        if (shader && *shader) shader->Push();
        texture->Push();
    }
    void WaterMaterial::Pop(bool instanced)
    {
        assert(!instanced);
        texture->Pop();
        if (shader && *shader) shader->Pop();
    }

    bool WaterMaterial::IsOpaque()
    {
        return texture->IsOpaque();
    }
    GlEngine::TesselationType WaterMaterial::GetTesselationType()
    {
        return GlEngine::TesselationType::Triangles;
    }

    const char *WaterMaterial::name()
    {
        return "WaterMaterial";
    }
    WaterMaterial::operator bool()
    {
        return texture && *texture && shader && *shader;
    }
}
