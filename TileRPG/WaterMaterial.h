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
        virtual void Push(GlEngine::ShaderFactory::ShaderFactory &factory) override;

        virtual std::vector<GlEngine::ShaderFactory::ShaderProp*> properties() override;
        virtual std::vector<GlEngine::ShaderFactory::Attribute*> attributes() override;

        bool IsOpaque() override;
        GlEngine::TesselationType GetTesselationType() override;

        virtual std::string name() override;
        virtual operator bool() override;

    private:
        GlEngine::Texture *texture;
    };
}
