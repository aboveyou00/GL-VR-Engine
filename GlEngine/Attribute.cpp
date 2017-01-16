#include "stdafx.h"
#include "Attribute.h"
#include "Property.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Attribute::Attribute(std::vector<PropertySource*> propertySources, std::vector<Attribute*> dependentAttrs, std::vector<PropertySource*> fallbackSources)
            : _propertySources(propertySources), _dependentAttrs(), _fallbackSources(fallbackSources)
        {
            for (PropertySource* source : propertySources)
                _propertySources.push_back(source);
            for (Attribute* attr : dependentAttrs)
                _dependentAttrs.push_back(attr);
        }
        Attribute::~Attribute()
        {
        }

        const std::vector<Attribute*> &Attribute::dependentAttributes() const
        {
            return _dependentAttrs;
        }
        const std::vector<PropertySource*> Attribute::propertySources() const
        {
            return _propertySources;
        }

        const std::vector<PropertySource*> Attribute::fallbackSources() const
        {
            return _fallbackSources;
        }
        
#pragma region position
        Attribute attr_GlPosition = Attribute({
            { // Vertex
                new Snippet("[out:0] = [in:0] * vec4([in:1], 1);",{ &prop_ModelViewProjectionMatrix, &prop_Position },{ &prop_GlPosition }),

                //Fallback
                new Snippet("[out:0] = [in:0] * [in:1];",{ &prop_ViewMatrix, &prop_ModelMatrix },{ &prop_ModelViewMatrix }, PropertySourceFlag::Fallback),
                new Snippet("[out:0] = [in:0] * [in:1];",{ &prop_ProjectionMatrix, &prop_ModelViewMatrix },{ &prop_ModelViewProjectionMatrix }, PropertySourceFlag::Fallback),

                new Snippet("[out:0] = [in:0] * vec4([in:1], 0);",{ &prop_ModelViewMatrix, &prop_Normal },{ &prop_ModelViewNormal }, PropertySourceFlag::Fallback)
            },
            { // Fragment
            }
        });
#pragma endregion

#pragma region lighting
        Attribute attr_Blinn = Attribute({
            { //Vertex
            },
            { //Fragment
            }
        }, { &attr_SpecularLight, &attr_DiffuseLight, &attr_AmbientLight });
        Attribute attr_BlinnPhong = Attribute({
            { //Vertex
            },
            { //Fragment
            }
        }, { &attr_SpecularLight, &attr_DiffuseLight, &attr_AmbientLight });

        Attribute attr_SpecularLight = Attribute({
            { //Vertex
            },
            { //Fragment
            }
        }, { &attr_LightingFallbacks });
        Attribute attr_DiffuseLight = Attribute({
            { // Vertex
                new Snippet("[out:0] = [in:0] * [in:1] * clamp(dot([in:2], [in:3].xyz), 0.0, 1.0);", { &prop_ReflectionCoefficient, &prop_DiffuseLightColor, &prop_PointLightDirection, &prop_ModelViewNormal }, { &prop_DiffuseLightColor }),

                //Fallback
                (new Snippet("[temp:0] = [in:1] * vec4([in:0], 1);\n[temp:1] = [in:3] * vec4([in:2], 1);\n[out:0] = normalize([temp:1].xyz - [temp:0].xyz);", { &prop_Position, &prop_ModelViewMatrix, &prop_PointLightPosition, &prop_ViewMatrix }, { &prop_PointLightDirection }, PropertySourceFlag::Fallback))->WithTemps<Vector<4>, Vector<4>>()
            },
            { // Fragment
            }
        }, { &attr_LightingFallbacks });
        Attribute attr_AmbientLight = Attribute({
            { // Vertex
            },
            { // Fragment
                new Snippet("[out:0] = vec4([in:0] * [in:1], 1);", { &prop_AmbientLightColor, &prop_RgbColor },{ &prop_RgbaColor }, PropertySourceFlag::Fallback)
            }
        }, { &attr_LightingFallbacks });

        Attribute attr_LightingFallbacks = Attribute({
            { //Vertex
            },
            { //Fragment
                //new Snippet("[out:0] = vec4([in:0], 1) * [in:1];", { &prop_DiffuseLightColor, &prop_RgbaColor }, { &prop_RgbaColor }, PropertySourceFlag::Fallback),
                new Snippet("[out:0] = vec4([in:0] * [in:1], 1);", { &prop_DiffuseLightColor, &prop_RgbColor }, { &prop_RgbaColor }, PropertySourceFlag::Fallback),
                //new Snippet("[out:0] = vec4([in:0], 1);", { &prop_DiffuseLightColor }, { &prop_RgbaColor }, PropertySourceFlag::Fallback)
            }
        });
#pragma endregion
    }
}
