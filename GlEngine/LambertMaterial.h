#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED LambertMaterial : public Material
    {
    public:
        static LambertMaterial *Create(Texture *texture);

    private:
        LambertMaterial(Texture *texture);
        ~LambertMaterial();

    public:
        void Push(ShaderFactory::ShaderFactory &factory) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;
        virtual std::vector<ShaderFactory::Attribute*> attributes() override;

        virtual std::string name() override;
        virtual operator bool() override;

    private:
        Texture *texture;
        //ShaderFactory *instancedShader, *singleShader;
    };
}
