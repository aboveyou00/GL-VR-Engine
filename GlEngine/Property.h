#pragma once

#include "EnvironmentAttribute.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        enum class PropertyType
        {
            Bool,
            Int,
            Uint,
            Float,
            Double,

            Bvec2,
            Bvec3,
            Bvec4,

            Ivec2,
            Ivec3,
            Ivec4,

            Uvec2,
            Uvec3,
            Uvec4,

            Vec2,
            Vec3,
            Vec4,

            Dvec2,
            Dvec3,
            Dvec4,

            Mat2x2,
            Mat2x3,
            Mat2x4,
            Mat3x2,
            Mat3x3,
            Mat3x4,
            Mat4x2,
            Mat4x3,
            Mat4x4,

            Mat2 = Mat2x2,
            Mat3 = Mat3x3,
            Mat4 = Mat4x4,

            Sampler,
        };

        std::string PropertyTypeString(PropertyType type);

        union PropertyValue
        {
            PropertyValue();
            ~PropertyValue();

            bool _bool;
            int _int;
            unsigned _uint;
            float _float;
            double _double;

            Vector<2, bool> _bvec2;
            Vector<3, bool> _bvec3;
            Vector<4, bool> _bvec4;

            Vector<2, int> _ivec2;
            Vector<3, int> _ivec3;
            Vector<4, int> _ivec4;

            Vector<2, unsigned> _uvec2;
            Vector<3, unsigned> _uvec3;
            Vector<4, unsigned> _uvec4;

            Vector<2, float> _vec2;
            Vector<3, float> _vec3;
            Vector<4, float> _vec4;

            Vector<2, double> _dvec2;
            Vector<3, double> _dvec3;
            Vector<4, double> _dvec4;

            Matrix<2, 2> _mat2x2;
            Matrix<2, 3> _mat2x3;
            Matrix<2, 4> _mat2x4;
            Matrix<3, 2> _mat3x2;
            Matrix<3, 3> _mat3x3;
            Matrix<3, 4> _mat3x4;
            Matrix<4, 2> _mat4x2;
            Matrix<4, 3> _mat4x3;
            Matrix<4, 4> _mat4x4;
        };

        class ENGINE_SHARED Property
        {
        public:
            Property(std::string name, PropertyType datatype, bool isBuiltIn = false, int arraylength = -1);
            ~Property();

            std::string name;
            PropertyType datatype;
            int arraylength;
            PropertyValue value;
            bool isBuiltIn;

            std::string    DeclerationString(std::string prefix = "");
            std::string ValueString();

        private:
            template<int size, typename T>
            std::string VectorArgumentsString(Vector<size, T> vec)
            {
                std::string result = Util::ToString(vec[0]);
                for (int i = 1; i < size; i++)
                    result += ", " + Util::ToString(vec[i]);
                return result;
            }
            template<int rows, int cols, typename T>
            std::string MatrixArgumentsString(Matrix<rows, cols, T> mat)
            {
                std::string result = Util::ToString(mat[0][0]);
                for (int r = 0; r < rows; r++)
                    for (int c = 0; c < cols; c++)
                        if (r != 0 || c != 0)
                            result += ", " + Util::ToString(mat[r][c]);
                return result;
            }
        };

        extern ENGINE_SHARED Property prop_Color;
        
        extern ENGINE_SHARED Property prop_Position;
        extern ENGINE_SHARED Property prop_Normal;
        extern ENGINE_SHARED Property prop_UV;

        extern ENGINE_SHARED Property prop_modelMatrix;
        extern ENGINE_SHARED Property prop_viewMatrix;
        extern ENGINE_SHARED Property prop_projectionMatrix;

        extern ENGINE_SHARED Property prop_LightColor;
    }
}
