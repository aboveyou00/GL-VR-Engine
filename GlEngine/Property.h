#pragma once

#include "EnvironmentAttribute.h"
#include "ShaderProp.h"
#include "PropertyType_attribs.h"

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

            std::string DeclarationString(std::string prefix = "")
            {
                std::stringstream stream;
                stream << PropertyType_attribs<T>::glsl_name << " ";
                stream << prefix << name;
                if (arrayLength != -1) stream << "[" << arrayLength << "]";
                stream << ";\r\n";
                return stream.str();
            }
        };

        extern ENGINE_SHARED Property<Vector<3>> prop_RgbColor;
        extern ENGINE_SHARED Property<Vector<4>> prop_RgbaColor;
        
<<<<<<< HEAD
        extern ENGINE_SHARED Property prop_Position;
        extern ENGINE_SHARED Property prop_Normal;
        extern ENGINE_SHARED Property prop_UV;

        extern ENGINE_SHARED Property prop_modelMatrix;
        extern ENGINE_SHARED Property prop_viewMatrix;
        extern ENGINE_SHARED Property prop_projectionMatrix;
		extern ENGINE_SHARED Property prop_modelViewMatrix;
		extern ENGINE_SHARED Property prop_modelViewProjectionMatrix;

        extern ENGINE_SHARED Property prop_LightColor;
		
		extern ENGINE_SHARED Property prop_glPosition;
=======
        extern ENGINE_SHARED Property<Vector<4>> prop_GlPosition;
        //Should these be vec4 or vec3?
        extern ENGINE_SHARED Property<Vector<4>> prop_Normal;
        extern ENGINE_SHARED Property<Vector<4>> prop_UV;

        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_modelMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_viewMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_projectionMatrix;

        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_modelViewMatrix;
        extern ENGINE_SHARED Property<Matrix<4, 4>> prop_modelViewProjectionMatrix;

        //Should these be vec4 or vec3?
        extern ENGINE_SHARED Property<Vector<4>> prop_LightColor;
        extern ENGINE_SHARED Property<Vector<4>> prop_AmbientLightColor;
        extern ENGINE_SHARED Property<Vector<4>> prop_DiffuseLightColor;
        extern ENGINE_SHARED Property<Vector<4>> prop_DiffuseLightDirection;
>>>>>>> 9a332fad24e8f2e4cf0df4e95d7ead07270d041e
    }
}
