#include "stdafx.h"
#include "Property.h"

#include "StringUtils.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Property::Property(std::string name, PropertyType type, int arraylength)
            : name(name), datatype(datatype), arraylength(arraylength)
        {
        }
        Property::~Property()
        {
        }

        std::string Property::DeclerationString(std::string prefix)
        {
            return PropertyTypeString(datatype) + " " + prefix + name + (arraylength == -1 ? "" : Util::formatted("[%i]", arraylength));
        }

        std::string Property::ValueString()
        {
            std::string inner_str;
            switch (datatype)
            {
            case PropertyType::Bool:
                return Util::ToString(value._bool);
            case PropertyType::Int:
                return Util::ToString(value._int);
            case PropertyType::Uint:
                return Util::ToString(value._uint);
            case PropertyType::Float:
                return Util::ToString(value._float);
            case PropertyType::Double:
                return Util::ToString(value._double);
            
            case PropertyType::Bvec2:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._bvec2) + ")";
            case PropertyType::Bvec3:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._bvec3) + ")";
            case PropertyType::Bvec4:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._bvec4) + ")";
            case PropertyType::Ivec2:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._ivec2) + ")";
            case PropertyType::Ivec3:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._ivec3) + ")";
            case PropertyType::Ivec4:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._ivec4) + ")";
            case PropertyType::Uvec2:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._uvec2) + ")";
            case PropertyType::Uvec3:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._uvec3) + ")";
            case PropertyType::Uvec4:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._uvec4) + ")";
            case PropertyType::Vec2:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._vec2) + ")";
            case PropertyType::Vec3:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._vec3) + ")";
            case PropertyType::Vec4:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._vec4) + ")";
            case PropertyType::Dvec2:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._dvec2) + ")";
            case PropertyType::Dvec3:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._dvec3) + ")";
            case PropertyType::Dvec4:
                return PropertyTypeString(datatype) + "(" + VectorArgumentsString(value._dvec4) + ")";

            case PropertyType::Mat2x2:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat2x2) + ")";
            case PropertyType::Mat2x3:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat2x3) + ")";
            case PropertyType::Mat2x4:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat2x4) + ")";
            case PropertyType::Mat3x2:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat3x2) + ")";
            case PropertyType::Mat3x3:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat3x3) + ")";
            case PropertyType::Mat3x4:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat3x4) + ")";
            case PropertyType::Mat4x2:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat4x2) + ")";
            case PropertyType::Mat4x3:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat4x3) + ")";
            case PropertyType::Mat4x4:
                return PropertyTypeString(datatype) + "(" + MatrixArgumentsString(value._mat4x4) + ")";

            }
        }

        Property prop_Color("color", PropertyType::Vec4);

        Property prop_Position("position", PropertyType::Vec4);
        Property prop_Normal("normal", PropertyType::Vec4);
        Property prop_UV("uv", PropertyType::Vec2);

        Property prop_ModelMatrix("model_matrix", PropertyType::Mat4);
        Property prop_ViewMatrix("view_matrix", PropertyType::Mat4);
        Property prop_ProjectionMatrix("projection_matrix", PropertyType::Mat4);

        Property prop_LightColor("light_color", PropertyType::Vec4);

        Property prop_AmbientLightColor("ambient_light_color", PropertyType::Vec4);
        Property prop_DiffuseLightColor("diffuse_light_color", PropertyType::Vec4);
        Property prop_DiffuseLightDirection("diffuse_light_direction", PropertyType::Vec4);
    }
}