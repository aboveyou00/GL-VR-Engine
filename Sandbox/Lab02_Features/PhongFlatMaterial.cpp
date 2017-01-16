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
    if (texture == nullptr)
    {
        factory.ProvideProperty(GlEngine::ShaderFactory::prop_RgbColor, color);
    }
    else
    {
        assert(false);
    }
    factory.ProvideProperty(GlEngine::ShaderFactory::prop_ReflectionCoefficient, reflectionCoef);
    factory.ProvideProperty(GlEngine::ShaderFactory::prop_Shininess, shininess);

    //auto shader = instanced ? instancedShader : singleShader;
    //if (shader && *shader) shader->Push();
    //texture->Push();
}
//void PhongFlatMaterial::Pop(bool instanced)
//{
//    instanced;
//    texture->Pop();
//    //auto shader = instanced ? instancedShader : singleShader;
//    //if (shader && *shader) shader->Pop();
//}

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
    if (texture == nullptr)
    {
        return {
            &GlEngine::ShaderFactory::prop_RgbColor,
            &GlEngine::ShaderFactory::prop_ReflectionCoefficient,
            &GlEngine::ShaderFactory::prop_Shininess
        };
    }
    else
    {
        assert(false);
        return {};
        //return {
        //    &ShaderFactory::prop_Texture,
        //    &ShaderFactory::prop_ReflectionCoefficient,
        //    &ShaderFactory::prop_Shininess
        //};
    }
}
std::vector<GlEngine::ShaderFactory::Attribute*> PhongFlatMaterial::attributes()
{
    return {
        &GlEngine::ShaderFactory::attr_GlPosition,
        &GlEngine::ShaderFactory::attr_PhongFlat
    };
}

const char *PhongFlatMaterial::name()
{
    return "PhongFlatMaterial";
}
PhongFlatMaterial::operator bool()
{
    if (texture == nullptr) return true;
    return !!*texture;
}
