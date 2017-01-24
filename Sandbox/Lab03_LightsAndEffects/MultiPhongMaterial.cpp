#include "stdafx.h"
#include "MultiPhongMaterial.h"
#include "ShaderFactory.h"
#include "Attribute.h"
#include "Snippet.h"

MultiPhongMaterial::MultiPhongMaterial(Vector<3> color, Vector<3> reflectionCoef, float shininess)
    : texture(nullptr), color(color), reflectionCoef(reflectionCoef), shininess(shininess)
{
}
MultiPhongMaterial::MultiPhongMaterial(GlEngine::Texture *texture, Vector<3> reflectionCoef, float shininess)
    : texture(texture), reflectionCoef(reflectionCoef), shininess(shininess)
{
}
MultiPhongMaterial::~MultiPhongMaterial()
{
}

bool MultiPhongMaterial::IsOpaque()
{
    return true;
}

GlEngine::TesselationType MultiPhongMaterial::GetTesselationType()
{
    return GlEngine::TesselationType::Disabled;
}

static Attribute attr_multi_phong = Attribute({
    { // Snippets
        new Snippet("[out:0] = [in:1].xyz;",
                    { &GlEngine::ShaderFactory::prop_PointLightInfo, &GlEngine::ShaderFactory::prop_GlPosition },
                    { &GlEngine::ShaderFactory::prop_LightColor },
                    GlEngine::ShaderFactory::PropertySourceFlag::None,
                    { GlEngine::ShaderFactory::ComponentType::Vertex })
    },
    { // Fallback Snippets
    },
    { //Dependent attributes
        &GlEngine::ShaderFactory::attr_GlPosition
    }
});

void MultiPhongMaterial::Push(ShaderFactory &factory)
{
    if (texture == nullptr) factory.ProvideProperty(GlEngine::ShaderFactory::prop_RgbColor, color);
    else factory.ProvideProperty(GlEngine::ShaderFactory::prop_Texture, texture);
    factory.ProvideProperty(GlEngine::ShaderFactory::prop_ReflectionCoefficient, reflectionCoef);
    factory.ProvideProperty(GlEngine::ShaderFactory::prop_Shininess, shininess);
}

std::vector<ShaderProp*> MultiPhongMaterial::properties()
{
    std::vector<ShaderProp*> props = {};
    if (texture == nullptr) props.push_back(&GlEngine::ShaderFactory::prop_RgbColor);
    else props.push_back(&GlEngine::ShaderFactory::prop_Texture);
    props.push_back(&GlEngine::ShaderFactory::prop_ReflectionCoefficient);
    props.push_back(&GlEngine::ShaderFactory::prop_Shininess);
    return props;
}
std::vector<Attribute*> MultiPhongMaterial::attributes()
{
    std::vector<Attribute*> attrs = {};
    if (texture == nullptr) attrs.push_back(&GlEngine::ShaderFactory::attr_RgbBaseColor);
    else attrs.push_back(&GlEngine::ShaderFactory::attr_TextureBaseColor);
    attrs.push_back(&GlEngine::ShaderFactory::attr_GlPosition);
    attrs.push_back(&attr_multi_phong);
    return attrs;
}

const char *MultiPhongMaterial::name()
{
    return "MultiPhongMaterial";
}

MultiPhongMaterial::operator bool()
{
    return true;
}
