#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED DiffuseMaterial : public Material
    {
    public:
        DiffuseMaterial(Vector<3> color, Vector<3> reflectionCoef);
        ~DiffuseMaterial();

    public:
        void Push(ShaderFactory::ShaderFactory &factory) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;
        virtual std::vector<ShaderFactory::Attribute*> attributes() override;

        virtual std::string name() override;

        virtual bool isReady() override;

    private:
        Vector<3> color;
        Vector<3> _reflectionCoef;
    };
}
