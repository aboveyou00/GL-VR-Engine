#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED DiffuseMaterial : public Material
    {
    public:
        static DiffuseMaterial *Create(Vector<3> color);

    private:
        DiffuseMaterial(Vector<3> color);
        ~DiffuseMaterial();

    public:
        void Push(ShaderFactory::ShaderFactory &factory) override;

        bool IsOpaque() override;
        TesselationType GetTesselationType() override;

        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;
        virtual std::vector<ShaderFactory::Attribute*> attributes() override;

        const char *name() override;
        operator bool() override;

    private:
        Vector<3> color;
    };
}
