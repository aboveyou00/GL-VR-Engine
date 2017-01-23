#include "stdafx.h"
#include "PhongFogMaterial.h"

#include "Snippet.h"
#include "ComponentType.h"
#include "Property.h"
using namespace GlEngine::ShaderFactory;

Property<float> prop_FogDistanceToCamera("fog_dist_to_camera");

Attribute attr_PhongFog(
    {
        new Snippet("[out:0] = distance(vec3([in:1] * vec4([in:0], 1)), [in:2]);"s,
                    { &prop_Position, &prop_ModelMatrix, &prop_CameraPosition },
                    { &prop_FogDistanceToCamera },
                    PropertySourceFlag::None,
                    { ComponentType::Vertex }),
        (new Snippet("[temp:0] = clamp(([in:0] - [in:1]) / ([in:2] - [in:1]), 0.0, 1.0) * [in:3].a;\n[out:0] = vec4(mix([in:4].xyz, [in:3].xyz, [temp:0]), [in:4].a);"s,
        //(new Snippet("[temp:0] = ([in:0] - [in:1]) / ([in:2] - [in:1]); [out:0] = vec4(mix([in:4].xyz, [in:3].xyz, [temp:0]), [in:4].a);"s,
                     { &prop_FogDistanceToCamera, &prop_FogMinDistance, &prop_FogMaxDistance, &prop_FogColor, &prop_RgbaColor },
                     { &prop_RgbaColor },
                     PropertySourceFlag::None,
                     { ComponentType::Fragment })
        )->WithTemps<float>()
    },
    {
    },
    {
        &attr_LightingFallbacks
    }
);

PhongFogMaterial::PhongFogMaterial(Vector<3> color, Vector<3> reflectionCoef, float shininess)
    : PhongMaterial(color, reflectionCoef, shininess)
{
}
PhongFogMaterial::PhongFogMaterial(GlEngine::Texture * texture, Vector<3> reflectionCoef, float shininess)
    : PhongMaterial(texture, reflectionCoef, shininess)
{
}
PhongFogMaterial::~PhongFogMaterial()
{
}

std::vector<GlEngine::ShaderFactory::Attribute*> PhongFogMaterial::attributes()
{
    auto attrs = PhongMaterial::attributes();
    attrs.push_back(&attr_PhongFog);
    return attrs;
}

const char *PhongFogMaterial::name()
{
    return "PhongFogMaterial";
}
