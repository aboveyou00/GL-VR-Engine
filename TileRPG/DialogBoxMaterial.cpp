#include "stdafx.h"
#include "DialogBoxMaterial.h"
#include "Texture.h"
#include "Shader.h"

namespace TileRPG
{
    DialogBoxMaterial::DialogBoxMaterial()
        : singleShader(GlEngine::Shader::Create("Shaders", "direct_light_tex"))
    {
    }
    DialogBoxMaterial::~DialogBoxMaterial()
    {
    }

    void DialogBoxMaterial::SetTexture(GlEngine::Texture *tex)
    {
        this->tex = tex;
    }

    void DialogBoxMaterial::Push(bool instanced)
    {
        assert(!instanced);
        if (singleShader && *singleShader) singleShader->Push();
        if (tex && *tex) tex->Push();
    }
    void DialogBoxMaterial::Pop(bool instanced)
    {
        assert(!instanced);
        if (tex && *tex) tex->Pop();
        if (singleShader && *singleShader) singleShader->Pop();
    }

    bool DialogBoxMaterial::IsOpaque()
    {
        return !tex || tex->IsOpaque();
    }
    GlEngine::TesselationType DialogBoxMaterial::GetTesselationType()
    {
        return GlEngine::TesselationType::Disabled;
    }

    const char *DialogBoxMaterial::name()
    {
        return "DialogBoxMaterial";
    }
    DialogBoxMaterial::operator bool()
    {
        return tex && *tex && singleShader && *singleShader;
    }
}
