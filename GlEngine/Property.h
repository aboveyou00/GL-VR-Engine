#pragma once

#include "ShaderProp.h"
#include "PropertyType_attribs.h"
#include <sstream>

namespace GlEngine
{
    namespace ShaderFactory
    {
        template <typename T>
        class ENGINE_SHARED Property : public ShaderProp
        {
        public:
            Property(std::string name, bool isBuiltIn = false, int arrayLength = -1)
                : ShaderProp(name, isBuiltIn, arrayLength)
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
                stream << PropertyType_attribs<T>::glsl_name << " ";
                stream << prefix << name;
                if (arrayLength != -1) stream << "[" << arrayLength << "]";
                return stream.str();
            }

            virtual unsigned LayoutSize() override
            {
                return arrayLength == -1 ? 1 : arrayLength;
            }
        };

#pragma region vertex-attributes
        extern ENGINE_SHARED Property<Vector<3>> prop_RgbColor;
        extern ENGINE_SHARED Property<Vector<4>> prop_RgbaColor;
       
        extern ENGINE_SHARED Property<Vector<3>> prop_Position;
        extern ENGINE_SHARED Property<Vector<3>> prop_Normal;
        extern ENGINE_SHARED Property<Vector<2>> prop_UV;
        extern ENGINE_SHARED Property<Vector<3>> prop_ReflectionCoefficient;

        extern ENGINE_SHARED Property<Vector<4>> prop_ModelViewNormal;

        extern ENGINE_SHARED Property<Vector<4>> prop_GlPosition;
#pragma endregion
        
#pragma region environment
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ModelMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ViewMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ProjectionMatrix;

        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ModelViewMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_ModelViewProjectionMatrix;

        extern ENGINE_SHARED Property<float> prop_GameTime;
#pragma endregion

#pragma region lighting
        //Should these be vec4 or vec3?
        extern ENGINE_SHARED Property<Vector<3>> prop_LightColor; //calculated using SpecularLightColor, DiffuseLightColor, and AmbientLightColor

        extern ENGINE_SHARED Property<Vector<3>> prop_SpecularLightColor;
        extern ENGINE_SHARED Property<Vector<3>> prop_DiffuseLightColor;
        extern ENGINE_SHARED Property<Vector<3>> prop_AmbientLightColor;

        extern ENGINE_SHARED Property<Vector<3>> prop_PointLightPosition;
        extern ENGINE_SHARED Property<Vector<3>> prop_PointLightDirection; //calculated using PointLightPosition
#pragma endregion
    }
}
