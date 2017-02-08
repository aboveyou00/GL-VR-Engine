#include "stdafx.h"
#include "PhongFlatMaterial.h"
#include "Texture.h"
#include "Shader.h"
#include "Property.h"
#include "Attribute.h"
#include "ShaderFactory.h"

PhongFlatMaterial::PhongFlatMaterial(Vector<3> color, Vector<3> reflectionCoef, float shininess)
    : texture(nullptr), color(color), reflectionCoef(reflectionCoef), shininess(shininess)
{
}
PhongFlatMaterial::PhongFlatMaterial(GlEngine::Texture *texture, Vector<3> reflectionCoef, float shininess)
    : texture(texture), reflectionCoef(reflectionCoef), shininess(shininess)
{
}
PhongFlatMaterial::~PhongFlatMaterial()
{
}

void PhongFlatMaterial::Push(GlEngine::ShaderFactory::ShaderFactory &factory)
{
    if (texture == nullptr) factory.ProvideProperty(GlEngine::ShaderFactory::prop_RgbColor, color);
    else factory.ProvideProperty(GlEngine::ShaderFactory::prop_Texture, texture);
    factory.ProvideProperty(GlEngine::ShaderFactory::prop_ReflectionCoefficient, reflectionCoef);
    factory.ProvideProperty(GlEngine::ShaderFactory::prop_Shininess, shininess);
}

bool PhongFlatMaterial::IsOpaque()
{
    if (texture == nullptr) return true;
    else return texture->IsOpaque();
}

GlEngine::TesselationType PhongFlatMaterial::GetTesselationType()
{
    return GlEngine::TesselationType::Disabled;
}

std::vector<GlEngine::ShaderFactory::ShaderProp*> PhongFlatMaterial::properties()
{
    std::vector<GlEngine::ShaderFactory::ShaderProp*> props = {};
    if (texture == nullptr) props.push_back(&GlEngine::ShaderFactory::prop_RgbColor);
    else props.push_back(&GlEngine::ShaderFactory::prop_Texture);
    props.push_back(&GlEngine::ShaderFactory::prop_ReflectionCoefficient);
    props.push_back(&GlEngine::ShaderFactory::prop_Shininess);
    return props;
}
std::vector<GlEngine::ShaderFactory::Attribute*> PhongFlatMaterial::attributes()
{
    std::vector<GlEngine::ShaderFactory::Attribute*> attrs = {};
    if (texture == nullptr) attrs.push_back(&GlEngine::ShaderFactory::attr_RgbBaseColor);
    else attrs.push_back(&GlEngine::ShaderFactory::attr_TextureBaseColor);
    attrs.push_back(&GlEngine::ShaderFactory::attr_GlPosition);
    attrs.push_back(&GlEngine::ShaderFactory::attr_PhongFlat);
    return attrs;
}

std::string PhongFlatMaterial::name()
{
    return "PhongFlatMaterial";
}
PhongFlatMaterial::operator bool()
{
    if (texture == nullptr) return true;
    return !!*texture;
}
