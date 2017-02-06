#include "stdafx.h"
#include "Attribute.h"
#include "Property.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Attribute::Attribute(std::vector<PropertySource*> propertySources, std::vector<PropertySource*> fallbackSources, std::vector<Attribute*> dependentAttrs)
            : _propertySources(), _dependentAttrs(), _fallbackSources(fallbackSources)
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

#pragma region outcolor
        Attribute attr_OutColor = Attribute(
            {
                new Snippet("",
                            { &prop_RgbaColor }, 
                            {}, 
                            PropertySourceFlag::None,
                            { ComponentType::Output })
            },
            {
            },
            { &attr_LightingFallbacks }
        );
#pragma endregion

#pragma region position
        Attribute attr_GlPosition = Attribute(
            {
                new Snippet("[out:0] = [in:0] * [in:1];",
                            { &prop_ViewMatrix, &prop_ModelMatrix },
                            { &prop_ModelViewMatrix }, 
                            PropertySourceFlag::Fallback),
                new Snippet("[out:0] = [in:0] * [in:1];",
                            { &prop_ProjectionMatrix, &prop_ModelViewMatrix },
                            { &prop_ModelViewProjectionMatrix }, 
                            PropertySourceFlag::Fallback ),
                new Snippet("[out:0] = [in:0] * vec4([in:1], 1);",
                            { &prop_ModelViewProjectionMatrix, &prop_Position }, 
                            { &prop_GlPosition }, 
                            PropertySourceFlag::None, 
                            { ComponentType::Vertex }),
            },
            {
            }
        );

        Attribute attr_ModelViewNormal = Attribute(
            {
                new Snippet("[out:0] = [in:0] * vec4([in:1], 0);",
                            { &prop_ModelViewMatrix, &prop_Normal },
                            { &prop_ModelViewNormal }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Vertex, ComponentType::Fragment })
            },
            {
            },
            { &attr_GlPosition }
        );

        static Attribute attr_NormalMap_Internal = Attribute(
            {
                new Snippet("[out:0] = (texture2D([in:1], [in:0]).xyz * 2) - 1;",
                             { &prop_UV, &prop_NormalMapTexture },
                             { &prop_Normal },
                             PropertySourceFlag::None,
                             { ComponentType::Fragment })
            },
            {
            },
            { }
        );
        Attribute attr_NormalMap = Attribute({ }, { }, { &attr_NormalMap_Internal, &attr_ModelViewNormal });
#pragma endregion

#pragma region base-color
        Attribute attr_RgbBaseColor = Attribute(
            {
                new Snippet("[out:0] = vec4([in:0], 1);",
                            { &prop_RgbColor },
                            { &prop_BaseColor },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment })
            },
            {
            }
        );
        Attribute attr_TextureBaseColor = Attribute(
            {
                new Snippet("[out:0] = texture2D([in:0], [in:1]);",
                            { &prop_Texture, &prop_UV },
                            { &prop_BaseColor },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment })
            },
            {
            }
        );
        Attribute attr_TwoTextureBaseColor = Attribute(
            {
                (new Snippet("[out:0] = texture2D([in:0], [in:2]);\n[temp:0] = texture2D([in:1], [in:2]);\n[out:0] = mix([out:0].rgba, vec4([temp:0].rgb, 1), [temp:0].a);//vec4(mix([out:0].rgb, [temp:0].rgb, [temp:0].a), 1 - ((1-[out:0].a) * (1-[temp:0].a)));",
                             { &prop_Texture, &prop_Texture2, &prop_UV },
                             { &prop_BaseColor },
                             PropertySourceFlag::None,
                             { ComponentType::Fragment }))->WithTemps<Vector<4>>()
            },
            {
            }
        );
        Attribute attr_AlphaMapDiscardBaseColor = Attribute(
            {
                (new Snippet("[temp:0] = texture2D([in:2], [in:1]).r;\nif ([temp:0] < .05) discard;\n[out:0] = vec4(texture2D([in:0], [in:1]).rgb, [temp:0]);",
                             { &prop_Texture, &prop_UV, &prop_AlphaMapTexture },
                             { &prop_BaseColor },
                             PropertySourceFlag::None,
                             { ComponentType::Fragment }))->WithTemps<float>()
            },
            {
            }
        );
#pragma endregion

#pragma region lighting
        Attribute attr_PointLightDirection = Attribute(
            {
                (new Snippet("[temp:0] = [in:2] * [in:1] * vec4([in:0], 1);\n[temp:1] = [in:2] * vec4([in:3], 1);\n[out:0] = normalize([temp:1].xyz - [temp:0].xyz);",
                             { &prop_Position, &prop_ModelMatrix, &prop_ViewMatrix, &prop_PointLightPosition },
                             { &prop_PointLightDirection },
                             PropertySourceFlag::Fallback,
                             { ComponentType::Fragment })
                )->WithTemps<Vector<4>, Vector<4>>()
            },
            {
            },
            { &attr_GlPosition }
        );

        Attribute attr_SpecularLight = Attribute(
            {
                new Snippet("[out:0] = normalize(vec3([in:2] * vec4([in:0], 1) - [in:2] * [in:1] * vec4([in:3], 1))); //normalized vector from surface position to camera position",
                            { &prop_CameraPosition, &prop_ModelMatrix, &prop_ViewMatrix, &prop_Position },
                            { &prop_SurfaceToCamera },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment }),
                
                (new Snippet("if (gl_FrontFacing) [temp:0] = normalize(reflect([in:2], vec3([in:3]))); //light direction reflected across the normal\n"s + 
                             "else [temp:0] = normalize(reflect([in:2], vec3(-[in:3])));\n"s + 
                             "[out:0] = [in:0] * [in:1] * pow(clamp(dot([temp:0], -[in:4]), 0.0, 1.0), [in:5]); //specular light calculation"s,
                             { &prop_ReflectionCoefficient, &prop_SpecularLightColor, &prop_PointLightDirection, &prop_ModelViewNormal, &prop_SurfaceToCamera, &prop_Shininess },
                             { &prop_SpecularLightComponent },
                             PropertySourceFlag::None,
                             { ComponentType::Fragment })
                )->WithTemps<Vector<3>>()
            },
            {
            },
            { &attr_ModelViewNormal, &attr_PointLightDirection }
        );

        Attribute attr_SpecularLightDirectional = Attribute(
        {
            new Snippet("[out:0] = normalize(vec3([in:2] * vec4([in:0], 1) - [in:2] * [in:1] * vec4([in:3], 1))); //normalized vector from surface position to camera position",
            { &prop_CameraPosition, &prop_ModelMatrix, &prop_ViewMatrix, &prop_Position },
            { &prop_SurfaceToCamera },
            PropertySourceFlag::None,
            { ComponentType::Fragment }),

            (new Snippet("if (gl_FrontFacing) [temp:0] = normalize(reflect([in:2], vec3([in:3]))); //light direction reflected across the normal\n"s +
            "else [temp:0] = normalize(reflect([in:2], vec3(-[in:3])));\n"s +
                "[out:0] = [in:0] * [in:1] * pow(clamp(dot([temp:0], -[in:4]), 0.0, 1.0), [in:5]); //specular light calculation"s,
                { &prop_ReflectionCoefficient, &prop_SpecularLightColor, &prop_DirectionalLightDirection, &prop_ModelViewNormal, &prop_SurfaceToCamera, &prop_Shininess },
                { &prop_SpecularLightComponent },
                PropertySourceFlag::None,
                { ComponentType::Fragment })
                )->WithTemps<Vector<3>>()
        },
        {
        },
        { &attr_ModelViewNormal }
        );
 
        Attribute attr_DiffuseIntensity = Attribute(
            {
                new Snippet("[out:0] = dot([in:0], [in:1].xyz);",
                            { &prop_PointLightDirection, &prop_ModelViewNormal },
                            { &prop_DiffuseComponentIntensity },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment })
            },
            {
            },
            { &attr_ModelViewNormal, &attr_PointLightDirection }
        );

        Attribute attr_DiffuseIntensityDirectional = Attribute(
            {
                new Snippet("[out:0] = dot([in:0], [in:1].xyz);",
                            { &prop_DirectionalLightDirection, &prop_ModelViewNormal },
                            { &prop_DiffuseComponentIntensity },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment }),
            },
            {
            },
            { &attr_ModelViewNormal }
        );

        Attribute attr_DiffuseLight = Attribute(
            {
                new Snippet("if (!gl_FrontFacing) [out:0] = -[in:2];\n[out:1] = [in:0] * [in:1] * clamp([in:2], 0.0, 1.0);",
                            { &prop_ReflectionCoefficient, &prop_DiffuseLightColor, &prop_DiffuseComponentIntensity },
                            { &prop_DiffuseComponentIntensity, &prop_DiffuseLightComponent },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment }),
            },
            {
            }, 
            { &attr_DiffuseIntensity }
        );

        Attribute attr_DiffuseLightDirectional = Attribute(
            {
                new Snippet("if (!gl_FrontFacing) [out:0] = -[in:2];\n[out:1] = [in:0] * [in:1] * clamp([in:2], 0.0, 1.0);",
                { &prop_ReflectionCoefficient, &prop_DiffuseLightColor, &prop_DiffuseComponentIntensity },
                { &prop_DiffuseComponentIntensity, &prop_DiffuseLightComponent },
                PropertySourceFlag::None,
                { ComponentType::Fragment }),
            },
            {
            },
            { &attr_DiffuseIntensityDirectional }
        );

        Attribute attr_DiffuseLightFlat = Attribute(
            {
                new Snippet("[out:0] = [in:0] * [in:1] * clamp(dot([in:2], [in:3].xyz), 0.0, 1.0);",
                            { &prop_ReflectionCoefficient, &prop_DiffuseLightColor, &prop_PointLightDirection, &prop_ModelViewNormal },
                            { &prop_DiffuseLightComponentFlat },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment })
            },
            {
            }, 
            { &attr_PointLightDirection }
        );


        Attribute attr_SpecularOnly = Attribute(
            {
                new Snippet("[out:0] = [in:0];",
                            { &prop_SpecularLightComponent },
                            { &prop_LightColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })
            },
            {
            },
            { &attr_SpecularLight }
        );
        
        Attribute attr_DiffuseOnly = Attribute(
            {
                new Snippet("[out:0] = [in:0];",
                            { &prop_DiffuseLightComponent },
                            { &prop_LightColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })
            },
            {
            },
            { &attr_DiffuseLight });
        
        Attribute attr_AmbientOnly = Attribute(
            {
                new Snippet("[out:0] = [in:0];",
                            { &prop_AmbientLightColor },
                            { &prop_LightColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })
            },
            {
            }, 
            { }
        );

        Attribute attr_AmbientDiffuse = Attribute(
            {
                new Snippet("[out:0] = [in:0] + [in:1];",
                            { &prop_AmbientLightColor, &prop_DiffuseLightComponent },
                            { &prop_LightColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })
            },
            {
            },
            { &attr_DiffuseLight }
        );

        Attribute attr_Phong = Attribute(
            { 
                //new Snippet("[out:0] = ([in:0] / 2) + vec3(.5, .5, .5);", { &prop_SpecularLightComponent }, { &prop_LightColor }, SnippetFlag::Fallback),
                //new Snippet("[out:0] = [in:0];", { &prop_SpecularLightComponent }, { &prop_LightColor }, SnippetFlag::Fallback),
                new Snippet("[out:0] = [in:0] + [in:1] + [in:2];",
                            { &prop_AmbientLightColor, &prop_DiffuseLightComponent, &prop_SpecularLightComponent },
                            { &prop_LightColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })
            },
            {
            }, 
            { &attr_SpecularLight, &attr_DiffuseLight }
        );

        Attribute attr_PhongDirectional = Attribute(
            {
                new Snippet("[out:0] = [in:0] + [in:1] + [in:2];",
                            { &prop_AmbientLightColor, &prop_DiffuseLightComponent, &prop_SpecularLightComponent },
                            { &prop_LightColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })                
            },
            {
            },
            { &attr_SpecularLightDirectional, &attr_DiffuseLightDirectional }
        );

        Attribute attr_PhongFlat = Attribute(
            {
                //new Snippet("[out:0] = ([in:0] / 2) + vec3(.5, .5, .5);", { &prop_SpecularLightComponent }, { &prop_LightColor }, SnippetFlag::Fallback),
                //new Snippet("[out:0] = [in:0];", { &prop_SpecularLightComponent }, { &prop_LightColor }, SnippetFlag::Fallback),
                new Snippet("[out:0] = [in:0] + [in:1] + [in:2];",
                            { &prop_AmbientLightColor, &prop_DiffuseLightComponentFlat, &prop_SpecularLightComponent },
                            { &prop_LightColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })
            },
            { 
            }, 
            { &attr_SpecularLight, &attr_DiffuseLightFlat }
        );

        Attribute attr_BlinnPhong = Attribute(
            {
                new Snippet("[out:0] = [in:0] + [in:1] + [in:2];",
                            { &prop_AmbientLightColor, &prop_DiffuseLightComponent, &prop_SpecularLightComponent },
                            { &prop_LightColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })
            },
            {
            },
            { &attr_SpecularLight, &attr_DiffuseLight }
        );

        Attribute attr_CelShading = Attribute(
            {
                new Snippet("[out:0] = round([in:0] * ([in:1] - 1)) / ([in:1] - 1);",
                            { &prop_DiffuseComponentIntensity, &prop_CelLevels },
                            { &prop_DiffuseComponentIntensity },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment })
            },
            {
            },
            { &attr_DiffuseIntensity }
        );

        static Property<float> prop_SpotFactor = Property<float>("spotlight_spot_factor");
        //static Property<float> prop_SpotlightRelativeDirection = Property<float>("spotlight_relative_direction");

        Attribute attr_Spotlight = Attribute(
            {
                //(new Snippet("[temp:0] = [in:2] * [in:1] * vec4([in:0], 1);\n[temp:1] = [in:4] * vec4([in:3], 1);\n[out:0] = normalize([temp:1].xyz - [temp:0].xyz);",
                //             { &prop_Position, &prop_ModelMatrix, &prop_ViewMatrix, &prop_SpotlightPosition, &prop_ViewMatrix },
                //             { &prop_SpotlightRelativeDirection },
                //             PropertySourceFlag::Fallback,
                //             { ComponentType::Fragment })
                //)->WithTemps<Vector<4>, Vector<4>>(),

                (new Snippet("[temp:0] = dot(-[in:0], ([in:1] * vec4([in:2], 0)).xyz);\n"s +
                             "if ([temp:0] > cos([in:4])) [out:0] = pow([temp:0], [in:3]);\n"s +
                             "else [out:0] = 0;",
                             { &prop_PointLightDirection, &prop_ViewMatrix, &prop_SpotlightDirection, &prop_SpotlightAttenuation, &prop_SpotlightCutoffAngle },
                             { &prop_SpotFactor },
                             PropertySourceFlag::None,
                             { ComponentType::Fragment })
                )->WithTemps<float>(),

                new Snippet("[out:0] = [in:0] * [in:1];",
                            { &prop_DiffuseLightComponent, &prop_SpotFactor },
                            { &prop_DiffuseLightComponent },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment }),

                new Snippet("[out:0] = [in:0] * [in:1];",
                            { &prop_SpecularLightComponent, &prop_SpotFactor },
                            { &prop_SpecularLightComponent },
                            PropertySourceFlag::None,
                            { ComponentType::Fragment })
            },
            {
            },
            { &attr_PointLightDirection, &attr_SpecularLight, &attr_DiffuseLight }
        );

        Attribute attr_LightingFallbacks = Attribute(
            {
                new Snippet("[out:0] = vec4([in:0], 1) * [in:1];",
                            { &prop_LightColor, &prop_BaseColor },
                            { &prop_RgbaColor }, 
                            PropertySourceFlag::Fallback,
                            { ComponentType::Fragment })
            },
            {
            },
            { }
        );

#pragma endregion
    }
}
