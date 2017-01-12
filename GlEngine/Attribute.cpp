#include "stdafx.h"
#include "Attribute.h"
#include "Property.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Attribute::Attribute(ComponentArray<std::vector<Snippet*>> snippets, std::vector<Attribute*> dependentAttrs)
            : _snippets({}), _dependentAttrs({})
        {
            for (auto type = ComponentType::Input; type <= ComponentType::Output; type++)
            {
                auto &comp_snippets = snippets[type];
                for (size_t q = 0; q < comp_snippets.size(); q++)
                    this->_snippets[type].push_back(comp_snippets[q]->Copy());
            }

            for (size_t q = 0; q < dependentAttrs.size(); q++)
                _dependentAttrs.push_back(dependentAttrs[q]);
        }
        Attribute::~Attribute()
        {
            for (auto type = ComponentType::Input; type <= ComponentType::Output; type++)
            {
                auto &comp_snippets = this->_snippets[type];
                for (size_t q = 0; q < comp_snippets.size(); q++)
                    delete comp_snippets[q];
            }
        }

        const std::vector<Attribute*> &Attribute::dependentAttributes() const
        {
            return _dependentAttrs;
        }
        const ComponentArray<std::vector<Snippet*>> &Attribute::snippets() const
        {
            return _snippets;
        }
        
#pragma region position
        Attribute attr_GlPosition = Attribute({
            { // Vertex
                new Snippet("[out:0] = [in:0] * vec4([in:1], 1);", { &prop_ModelViewProjectionMatrix, &prop_Position }, { &prop_GlPosition }),

                //Fallback
                new Snippet("[out:0] = [in:0] * [in:1];", { &prop_ViewMatrix, &prop_ModelMatrix }, { &prop_ModelViewMatrix }, SnippetFlag::Fallback),
                new Snippet("[out:0] = [in:0] * [in:1];", { &prop_ProjectionMatrix, &prop_ModelViewMatrix }, { &prop_ModelViewProjectionMatrix }, SnippetFlag::Fallback),

                new Snippet("[out:0] = [in:0] * vec4([in:1], 0);", { &prop_ModelViewMatrix, &prop_Normal }, { &prop_ModelViewNormal }, SnippetFlag::Fallback)
            },
            { // Fragment
            }
        });
#pragma endregion

#pragma region lighting
        Attribute attr_SpecularLight = Attribute({
            { //Vertex
                new Snippet("[out:0] = vec3(0, 0, 0);", { }, { &prop_SpecularLightColor })
            },
            { //Fragment
            }
        }, { &attr_LightingFallbacks });
        Attribute attr_DiffuseLight = Attribute({
            { // Vertex
                new Snippet("[out:0] = [in:0] * [in:1] * clamp(dot([in:2], [in:3].xyz), 0.0, 1.0);", { &prop_ReflectionCoefficient, &prop_DiffuseLightColor, &prop_PointLightDirection, &prop_ModelViewNormal }, { &prop_DiffuseLightColor }),

                //Fallback
                (new Snippet("[temp:0] = [in:1] * vec4([in:0], 1);\n[temp:1] = [in:3] * vec4([in:2], 1);\n[out:0] = normalize([temp:1].xyz - [temp:0].xyz);", { &prop_Position, &prop_ModelViewMatrix, &prop_PointLightPosition, &prop_ViewMatrix }, { &prop_PointLightDirection }, SnippetFlag::Fallback))->WithTemps<Vector<4>, Vector<4>>()
            },
            { // Fragment
            }
        }, { &attr_LightingFallbacks });

        Attribute attr_SpecularOnly = Attribute({
            { // Vertex
            },
            { // Fragment
                new Snippet("[out:0] = [in:0];", { &prop_SpecularLightColor }, { &prop_LightColor }, SnippetFlag::Fallback)
            }
        }, { &attr_SpecularLight, &attr_LightingFallbacks });
        Attribute attr_DiffuseOnly = Attribute({
            { // Vertex
            },
            { // Fragment
                new Snippet("[out:0] = [in:0];", { &prop_DiffuseLightColor }, { &prop_LightColor }, SnippetFlag::Fallback)
            }
        }, { &attr_DiffuseLight, &attr_LightingFallbacks });
        Attribute attr_AmbientOnly = Attribute({
            { // Vertex
            },
            { // Fragment
                new Snippet("[out:0] = [in:0];", { &prop_AmbientLightColor }, { &prop_LightColor }, SnippetFlag::Fallback)
            }
        }, { &attr_LightingFallbacks });
        
        Attribute attr_AmbientDiffuse = Attribute({
            { // Vertex
            },
            { // Fragment
                new Snippet("[out:0] = [in:0] + [in:1];", { &prop_AmbientLightColor, &prop_DiffuseLightColor }, { &prop_LightColor }, SnippetFlag::Fallback)
            }
        }, { &attr_DiffuseLight });

        Attribute attr_Phong = Attribute({
            { //Vertex
            },
            { //Fragment
                new Snippet("[out:0] = [in:0] + [in:1] + [in:2];", { &prop_AmbientLightColor, &prop_DiffuseLightColor, &prop_SpecularLightColor }, { &prop_LightColor }, SnippetFlag::Fallback)
            }
        }, { &attr_SpecularLight, &attr_DiffuseLight });
        Attribute attr_BlinnPhong = Attribute({
            { //Vertex
            },
            { //Fragment
                new Snippet("[out:0] = [in:0] + [in:1] + [in:2];", { &prop_AmbientLightColor, &prop_DiffuseLightColor, &prop_SpecularLightColor }, { &prop_LightColor }, SnippetFlag::Fallback)
            }
        }, { &attr_SpecularLight, &attr_DiffuseLight });

        Attribute attr_LightingFallbacks = Attribute({
            { //Vertex
            },
            { //Fragment
                new Snippet("[out:0] = vec4([in:0] * [in:1], 1);", { &prop_LightColor, &prop_RgbColor }, { &prop_RgbaColor }, SnippetFlag::Fallback)
            }
        });
#pragma endregion
    }
}
