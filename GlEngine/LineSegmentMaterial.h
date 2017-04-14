#pragma once

#include "Material.h"

namespace GlEngine
{
    class ENGINE_SHARED LineSegmentMaterial: public Material
    {
    public:
        LineSegmentMaterial(bool is2d = false);
        ~LineSegmentMaterial();

        virtual void Push(ShaderFactory::ShaderFactory &factory) override;

        virtual std::vector<ShaderFactory::Attribute*> attributes() override;
        virtual std::vector<ShaderFactory::ShaderProp*> properties() override;

        virtual bool IsOpaque() override;

        virtual TesselationType GetTesselationType() override;
    };
}
