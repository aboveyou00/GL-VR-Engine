#include "stdafx.h"
#include "PhongMaterial.h"
#include "Texture.h"
#include "Shader.h"
#include "Property.h"
#include "Attribute.h"
#include "ShaderFactory.h"

namespace GlEngine
{
    PhongMaterial::PhongMaterial(Vector<3> color, Vector<3> reflectionCoef, float shininess)
        : Material("PhongMaterial"), texture(nullptr), texture2(nullptr), _color(color), _reflectionCoef(reflectionCoef), _shininess(shininess)
    {
    }
    PhongMaterial::PhongMaterial(Texture *texture, Vector<3> reflectionCoef, float shininess)
        : Material("PhongMaterial"), texture(texture), texture2(nullptr), _reflectionCoef(reflectionCoef), _shininess(shininess)
    {
    }
    PhongMaterial::PhongMaterial(Texture *texture, Texture *texture2, Vector<3> reflectionCoef, float shininess)
        : Material("PhongMaterial"), texture(texture), texture2(texture2), _reflectionCoef(reflectionCoef), _shininess(shininess)
    {
    }
    PhongMaterial::~PhongMaterial()
    {
    }

    void PhongMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        if (texture == nullptr) factory.ProvideProperty(ShaderFactory::prop_RgbColor, _color);
        else
        {
            factory.ProvideProperty(ShaderFactory::prop_Texture, texture);
            if (texture2 != nullptr)
            {
                if (texture2->hasFlag(TextureFlag::AlphaMap)) factory.ProvideProperty(GlEngine::ShaderFactory::prop_AlphaMapTexture, texture2);
                else if (texture2->hasFlag(TextureFlag::NormalMask)) factory.ProvideProperty(ShaderFactory::prop_NormalMapTexture, texture2);
                else factory.ProvideProperty(ShaderFactory::prop_Texture2, texture2);
            }
        }
        factory.ProvideProperty(ShaderFactory::prop_ReflectionCoefficient, _reflectionCoef);
        factory.ProvideProperty(ShaderFactory::prop_Shininess, _shininess);
    }

    bool PhongMaterial::IsOpaque()
    {
        if (texture == nullptr) return true;
        else return texture->IsOpaque();
    }

    TesselationType PhongMaterial::GetTesselationType()
    {
        return TesselationType::Disabled;
    }

    std::vector<ShaderFactory::ShaderProp*> PhongMaterial::properties()
    {
        std::vector<ShaderFactory::ShaderProp*> props = { };
        if (texture == nullptr) props.push_back(&ShaderFactory::prop_RgbColor);
        else
        {
            props.push_back(&ShaderFactory::prop_Texture);
            if (texture2 != nullptr)
            {
                if (texture2->hasFlag(TextureFlag::AlphaMap)) props.push_back(&GlEngine::ShaderFactory::prop_AlphaMapTexture);
                else if (texture2->hasFlag(TextureFlag::NormalMask)) props.push_back(&ShaderFactory::prop_NormalMapTexture);
                else props.push_back(&GlEngine::ShaderFactory::prop_Texture2);
            }
        }
        props.push_back(&ShaderFactory::prop_ReflectionCoefficient);
        props.push_back(&ShaderFactory::prop_Shininess);
        return props;
    }
    std::vector<ShaderFactory::Attribute*> PhongMaterial::attributes()
    {
        std::vector<ShaderFactory::Attribute*> attrs = { };
        if (texture == nullptr) attrs.push_back(&ShaderFactory::attr_RgbBaseColor);
        else
        {
            if (texture2 != nullptr)
            {
                if (texture2->hasFlag(TextureFlag::AlphaMap)) attrs.push_back(&ShaderFactory::attr_AlphaMapDiscardBaseColor);
                else if (texture2->hasFlag(TextureFlag::NormalMask))
                {
                    attrs.push_back(&ShaderFactory::attr_NormalMap);
                    attrs.push_back(&ShaderFactory::attr_TextureBaseColor);
                }
                else attrs.push_back(&ShaderFactory::attr_TwoTextureBaseColor);
            }
            else attrs.push_back(&ShaderFactory::attr_TextureBaseColor);
        }
        attrs.push_back(&ShaderFactory::attr_GlPosition);
        attrs.push_back(&ShaderFactory::attr_Phong);
        return attrs;
    }

    std::string PhongMaterial::name()
    {
        return "PhongMaterial";
    }

    bool PhongMaterial::isReady()
    {
        if (texture == nullptr) return true;
        return texture->isReady() && (texture2 == nullptr || texture2->isReady());
    }

    const Vector<3> &PhongMaterial::color() const noexcept
    {
        return _color;
    }
    const Vector<3> &PhongMaterial::reflectionCoef() const noexcept
    {
        return _reflectionCoef;
    }
    const float PhongMaterial::shininess() const noexcept
    {
        return _shininess;
    }

    void PhongMaterial::SetColor(Vector<3> color) noexcept
    {
        _color = color;
    }
    void PhongMaterial::SetReflectionCoef(Vector<3> coef) noexcept
    {
        _reflectionCoef = coef;
    }
    void PhongMaterial::SetShininess(float shininess) noexcept
    {
        _shininess = shininess;
    }
}
