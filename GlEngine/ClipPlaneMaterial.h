#pragma once
#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED ClipPlaneMaterial : public Material
    {
    public:
        ClipPlaneMaterial(std::string name, Vector<4> color);
        ClipPlaneMaterial(std::string name, Texture *tex);
        ~ClipPlaneMaterial();

        virtual void Push(ShaderFactory::ShaderFactory &factory) override;

        virtual std::vector<ShaderFactory::Attribute*> attributes() override;
        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;

        virtual bool IsOpaque() override;
        virtual TesselationType GetTesselationType() override;

        virtual bool isReady() override;

    private:
        Texture *tex;
        Vector<4> color;
    };
}
