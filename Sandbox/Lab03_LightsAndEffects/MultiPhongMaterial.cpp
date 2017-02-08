#include "stdafx.h"
#include "MultiPhongMaterial.h"
#include "ShaderFactory.h"
#include "Attribute.h"
#include "Snippet.h"
using namespace GlEngine::ShaderFactory;

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
    "attr_multi_phong"s,
    { // Snippets
        new Snippet("[out:0] = normalize(vec3([in:2] * vec4([in:0], 1) - [in:2] * [in:1] * vec4([in:3], 1))); //normalized vector from surface position to camera position",
                    { &prop_CameraPosition, &prop_ModelMatrix, &prop_ViewMatrix, &prop_Position },
                    { &prop_SurfaceToCamera },
                    PropertySourceFlag::None,
                    { ComponentType::Vertex }),

        (new Snippet(R"raw(//MULTI_PHONG BEGIN
[out:0] = vec3(0, 0, 0);
[out:1] = vec3(0, 0, 0);

for ([temp:0] = 0; [temp:0] < 4; [temp:0]++)
{
    [temp:1] = [in:3] * [in:2] * vec4([in:1], 1);
    [temp:2] = [in:3] * vec4([in:0][[temp:0]].v0, 1);
    [temp:3] = normalize([temp:2].xyz - [temp:1].xyz); //[temp:3] is the point light direction

    if (gl_FrontFacing) [temp:4] = normalize(reflect([temp:3], vec3([in:4]))); //light direction reflected across the normal
    else [temp:4] = normalize(reflect([temp:3], vec3(-[in:4])));
    [out:0] += .25 * [in:7] * [in:0][[temp:0]].v1 * pow(clamp(dot([temp:4], -[in:5]), 0.0, 1.0), [in:6]); //specular light calculation

    [temp:5] = dot([temp:3], [in:4].xyz); //[temp:5] is the diffuse component intensity
    if (!gl_FrontFacing) [temp:5] = -[temp:5];
    [out:1] += .25 * [in:7] * [in:0][[temp:0]].v1 * clamp([temp:5], 0.0, 1.0);
}
//MULTI_PHONG END)raw"s,
                     { &prop_PointLightInfo, &prop_Position, &prop_ModelMatrix, &prop_ViewMatrix, &prop_ModelViewNormal, &prop_SurfaceToCamera, &prop_Shininess, &prop_ReflectionCoefficient },
                     { &prop_SpecularLightComponent, &prop_DiffuseLightComponent },
                     PropertySourceFlag::None,
                     { ComponentType::Fragment })
        )->WithTemps<int, Vector<4>, Vector<4>, Vector<3>, Vector<3>, float>(),

        new Snippet("[out:0] = [in:0] + [in:1] + [in:2];",
                     { &prop_AmbientLightColor, &prop_DiffuseLightComponent, &prop_SpecularLightComponent },
                     { &prop_LightColor }, 
                     PropertySourceFlag::Fallback,
                     { ComponentType::Fragment })
    },
    { // Fallback Snippets
    },
    { &attr_GlPosition, &attr_ModelViewNormal }
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

std::string MultiPhongMaterial::name()
{
    return "MultiPhongMaterial";
}

MultiPhongMaterial::operator bool()
{
    return true;
}
