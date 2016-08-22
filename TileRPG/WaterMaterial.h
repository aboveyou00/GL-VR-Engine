#pragma once

#include "Material.h"

namespace TileRPG
{
    class WaterMaterial : public GlEngine::Material
    {
    public:
        static WaterMaterial *GetInstance();

    private:
        WaterMaterial();
        ~WaterMaterial();

    public:
        void Push(bool instanced = false) override;
        void Pop(bool instanced = false) override;

        bool IsOpaque() override;
        GlEngine::TesselationType GetTesselationType() override;

        const char *name() override;
        operator bool() override;

    private:
        GlEngine::Texture *texture;
        GlEngine::ShaderFactory *shader;
    };
}
