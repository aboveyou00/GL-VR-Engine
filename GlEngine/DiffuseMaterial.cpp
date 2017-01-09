#include "stdafx.h"
#include "DiffuseMaterial.h"
#include "Shader.h"

#include "ShaderFactory.h"
#include "Property.h"
#include "Attribute.h"

#include "OpenGl.h"

namespace GlEngine
{
    DiffuseMaterial *DiffuseMaterial::Create(Vector<3> color)
    {
        static std::vector<DiffuseMaterial*> cache;
        for (auto ptr = cache.begin(); ptr != cache.end(); ptr++)
        {
            auto &mat = **ptr;
            if (mat.color == color) return &mat;
        }

        auto diffuse = new DiffuseMaterial(color);
        cache.push_back(diffuse);
        return diffuse;
    }

    DiffuseMaterial::DiffuseMaterial(Vector<3> color)
        : color(color)
    {
    }
    DiffuseMaterial::~DiffuseMaterial()
    {
    }

    void DiffuseMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        factory.ProvideProperty(ShaderFactory::prop_DiffuseLightColor, { color[0], color[1], color[2], 1.f });
    }

    bool DiffuseMaterial::IsOpaque()
    {
        return true;
    }

    TesselationType DiffuseMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> DiffuseMaterial::properties()
    {
        return {
            &ShaderFactory::prop_ModelViewMatrix,
            &ShaderFactory::prop_ProjectionMatrix,
            &ShaderFactory::prop_DiffuseLightPosition,
            &ShaderFactory::prop_DiffuseLightColor,
            &ShaderFactory::prop_RgbColor,
            &ShaderFactory::prop_ReflectionCoefficient
        };
    }
    std::vector<ShaderFactory::Attribute*> DiffuseMaterial::attributes()
    {
        return {
            &ShaderFactory::attr_GlPosition,
            &ShaderFactory::attr_DiffuseLight
        };
    }

    const char *DiffuseMaterial::name()
    {
        return "DiffuseMaterial";
    }
    DiffuseMaterial::operator bool()
    {
        return true;
    }
}
