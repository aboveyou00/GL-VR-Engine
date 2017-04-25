#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED AmbientMaterial : public Material
    {
    public:
        AmbientMaterial(Vector<3> color);
        AmbientMaterial(Texture *texture);
        ~AmbientMaterial();

    public:
        void Push(ShaderFactory::ShaderFactory &factory) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;
        virtual std::vector<ShaderFactory::Attribute*> attributes() override;

        virtual bool isReady() override;

    private:
        Vector<3> _color, _reflectionCoef;
        Texture *texture;
    };
}
