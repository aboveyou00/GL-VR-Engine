#pragma once

#include "ShaderProp.h"
#include "PropertyType_attribs.h"
#include "PointLightInfo.h"
#include <sstream>

namespace GlEngine
{
    class Texture;

    namespace ShaderFactory
    {
        template <typename T>
        class ENGINE_SHARED Property : public ShaderProp
        {
        public:
            Property(std::string name, PropertyFlag flags = PropertyFlag::None)
                : ShaderProp(name, PropertyType_attribs<T>::default_property_flags() | flags)
            {
            }
            ~Property()
            {
            }

            static std::string ValueString(const T val)
            {
                return PropertyType_attribs<T>::glsl_value(val);
            }

            std::string DeclarationString(std::string prefix = "") override
            {
                std::stringstream stream;
                PropertyType_attribs<T>::decl_string(stream, prefix, name);
                return stream.str();
            }

            virtual unsigned uniformSize() override
            {
                return PropertyType_attribs<T>::glsl_uniform_size();
            }
            virtual unsigned attributeSize() override
            {
                return PropertyType_attribs<T>::glsl_attribute_size();
            }
        };

#pragma region vertex-attributes
        extern ENGINE_SHARED Property<Vector<3>> prop_RgbColor;
        extern ENGINE_SHARED Property<Vector<4>> prop_BaseColor;
        extern ENGINE_SHARED Property<Vector<4>> prop_RgbaColor;

        extern ENGINE_SHARED Property<Vector<3>> prop_Position;
        extern ENGINE_SHARED Property<Vector<3>> prop_Normal;
        extern ENGINE_SHARED Property<Vector<2>> prop_UV;
        extern ENGINE_SHARED Property<Vector<3>> prop_ReflectionCoefficient;
        extern ENGINE_SHARED Property<float> prop_Shininess;

        extern ENGINE_SHARED Property<Vector<4>> prop_ModelViewNormal;

        extern ENGINE_SHARED Property<Vector<4>> prop_GlPosition;
        extern ENGINE_SHARED Property<Vector<4>> prop_GlFragCoord;

        extern ENGINE_SHARED Property<Texture*> prop_Texture;
        extern ENGINE_SHARED Property<Texture*> prop_Texture2;
        extern ENGINE_SHARED Property<Texture*> prop_AlphaMapTexture;
#pragma endregion

#pragma region environment
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ModelMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ViewMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ProjectionMatrix;

        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ModelViewMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ModelViewProjectionMatrix;

        extern ENGINE_SHARED Property<Vector<3>> prop_CameraPosition;

        extern ENGINE_SHARED Property<float> prop_GameTime;
#pragma endregion

#pragma region lighting
        //Should these be vec4 or vec3?
        extern ENGINE_SHARED Property<Vector<3>> prop_LightColor; //calculated using SpecularLightColor, DiffuseLightColor, and AmbientLightColor

        extern ENGINE_SHARED Property<Vector<3>> prop_SpecularLightComponent;
        extern ENGINE_SHARED Property<Vector<3>> prop_DiffuseLightComponent;
        extern ENGINE_SHARED Property<Vector<3>> prop_DiffuseLightComponentFlat;

        extern ENGINE_SHARED Property<Vector<3>> prop_SpecularLightColor;
        extern ENGINE_SHARED Property<Vector<3>> prop_DiffuseLightColor;
        extern ENGINE_SHARED Property<Vector<3>> prop_AmbientLightColor;

        extern ENGINE_SHARED Property<Vector<3>> prop_PointLightPosition;
        extern ENGINE_SHARED Property<Vector<3>> prop_PointLightDirection; //calculated using PointLightPosition

        extern ENGINE_SHARED Property<Array<PointLightInfo, 4>> prop_PointLightInfo;

        extern ENGINE_SHARED Property<Vector<3>> prop_SurfaceToCamera;
        extern ENGINE_SHARED Property<float> prop_DiffuseComponentIntensity;

        extern ENGINE_SHARED Property<float> prop_FogMinDistance;
        extern ENGINE_SHARED Property<float> prop_FogMaxDistance;
        extern ENGINE_SHARED Property<Vector<4>> prop_FogColor;

        extern ENGINE_SHARED Property<int> prop_CelLevels;

        extern ENGINE_SHARED Property<Vector<3>> prop_SpotlightPosition;
        extern ENGINE_SHARED Property<Vector<3>> prop_SpotlightColor;
        extern ENGINE_SHARED Property<Vector<3>> prop_SpotlightDirection;
        extern ENGINE_SHARED Property<float> prop_SpotlightAttenuation;
        extern ENGINE_SHARED Property<float> prop_SpotlightCutoffAngle;
#pragma endregion
    }
}
