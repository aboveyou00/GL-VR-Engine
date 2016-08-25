#pragma once

#include "Material.h"

namespace TileRPG
{
    class DialogBoxMaterial : public GlEngine::Material
    {
    public:
        DialogBoxMaterial();
        ~DialogBoxMaterial();

        void SetTexture(GlEngine::Texture *tex);

        void Push(bool instanced = false) override;
        void Pop(bool instanced = false) override;

        bool IsOpaque() override;
        GlEngine::TesselationType GetTesselationType() override;

        const char *name() override;
        operator bool() override;

    private:
        GlEngine::Texture *tex;
        GlEngine::Shader *singleShader;
    };
}
