#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED Image2dMaterial : public Material
    {
    public:
        Image2dMaterial();
        ~Image2dMaterial();

        void SetTexture(Texture *tex);

        void Push(ShaderFactory::ShaderFactory &factory) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;
        virtual std::vector<ShaderFactory::Attribute*> attributes() override;

        virtual std::string name() override;
        operator bool() override;

    private:
        Texture *tex;
        //Shader *singleShader;
    };
}
