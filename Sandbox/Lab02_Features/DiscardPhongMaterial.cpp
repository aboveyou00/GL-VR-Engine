#include "stdafx.h"
#include "DiscardPhongMaterial.h"
#include "Attribute.h"
#include "Snippet.h"

DiscardPhongMaterial::DiscardPhongMaterial(Vector<3> color, Vector<3> reflectionCoef, float shininess)
    : PhongMaterial(color, reflectionCoef, shininess)
{
}
DiscardPhongMaterial::DiscardPhongMaterial(Texture *texture, Vector<3> reflectionCoef, float shininess)
    : PhongMaterial(texture, reflectionCoef, shininess)
{
}
DiscardPhongMaterial::~DiscardPhongMaterial()
{
}

typedef GlEngine::ShaderFactory::Attribute Attribute;
typedef GlEngine::ShaderFactory::Snippet Snippet;
typedef GlEngine::ShaderFactory::PropertySourceFlag PropertySourceFlag;
typedef GlEngine::ShaderFactory::ComponentType ComponentType;

static Attribute attr_Discard = Attribute(
    "attr_Discard"s,
    {
        (new Snippet("[temp:0] = dot([in:0], [in:0]);\n[temp:1] = dot([in:1], [in:1]);\nif ([temp:0] > .75 && [temp:1] < .75) discard;", 
                     { &GlEngine::ShaderFactory::prop_DiffuseLightComponent, &GlEngine::ShaderFactory::prop_SpecularLightComponent }, 
                     {},
                     PropertySourceFlag::None,
                     { ComponentType::Fragment })
        )->WithTemps<float, float>()
    },
    { 
    }, {
    &GlEngine::ShaderFactory::attr_GlPosition,
    &GlEngine::ShaderFactory::attr_Phong
});

std::vector<GlEngine::ShaderFactory::Attribute*> DiscardPhongMaterial::attributes()
{
    auto attrs = PhongMaterial::attributes();
    attrs.push_back(&attr_Discard);
    return attrs;
}
std::string DiscardPhongMaterial::name()
{
    return "DiscardPhongMaterial";
}
