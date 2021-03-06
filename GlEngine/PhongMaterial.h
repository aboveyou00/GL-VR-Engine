#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED PhongMaterial : public Material
    {
    public:
        PhongMaterial(Vector<3> color, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
        PhongMaterial(Texture *texture, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
        PhongMaterial(Texture *texture1, Texture *texture2, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
        ~PhongMaterial();

    public:
        void Push(ShaderFactory::ShaderFactory &factory) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;
        virtual std::vector<ShaderFactory::Attribute*> attributes() override;

        virtual std::string name() override;

        virtual bool isReady() override;

    private:
        Texture *texture, *texture2;
        Vector<3> color, reflectionCoef;
        float shininess;
    };
}
