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
        : texture(nullptr), texture2(nullptr), color(color), reflectionCoef(reflectionCoef), shininess(shininess)
    {
    }
    PhongMaterial::PhongMaterial(Texture *texture, Vector<3> reflectionCoef, float shininess)
        : texture(texture), texture2(nullptr), reflectionCoef(reflectionCoef), shininess(shininess)
    {
    }
    PhongMaterial::PhongMaterial(Texture *texture, Texture *texture2, Vector<3> reflectionCoef, float shininess)
        : texture(texture), texture2(texture2), reflectionCoef(reflectionCoef), shininess(shininess)
    {
    }
    PhongMaterial::~PhongMaterial()
    {
    }

    void PhongMaterial::Push(ShaderFactory::ShaderFactory &factory)
    {
        if (texture == nullptr) factory.ProvideProperty(ShaderFactory::prop_RgbColor, color);
        else
        {
            factory.ProvideProperty(ShaderFactory::prop_Texture, texture);
            if (texture2 != nullptr)
            {
                if (texture2->hasFlag(TextureFlag::AlphaMap)) factory.ProvideProperty(GlEngine::ShaderFactory::prop_AlphaMapTexture, texture2);
                else factory.ProvideProperty(ShaderFactory::prop_Texture2, texture2);
            }
        }
        factory.ProvideProperty(ShaderFactory::prop_ReflectionCoefficient, reflectionCoef);
        factory.ProvideProperty(ShaderFactory::prop_Shininess, shininess);
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
                else attrs.push_back(&ShaderFactory::attr_TwoTextureBaseColor);
            }
            else attrs.push_back(&ShaderFactory::attr_TextureBaseColor);
        }
        attrs.push_back(&ShaderFactory::attr_GlPosition);
        attrs.push_back(&ShaderFactory::attr_Phong);
        return attrs;
    }

    const char *PhongMaterial::name()
    {
        return "PhongMaterial";
    }
    PhongMaterial::operator bool()
    {
        if (texture == nullptr) return true;
        return !!*texture && (texture2 == nullptr || !!*texture2);
    }
}
