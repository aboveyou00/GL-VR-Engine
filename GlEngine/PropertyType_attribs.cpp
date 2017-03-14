#include "stdafx.h"
#include "PropertyType_attribs.h"

#include "StringUtils.h"

#include "OpenGl.h"
#include "Texture.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
#pragma region util
        template<int size, typename T>
        std::string VectorArgumentsString(Vector<size, T> vec)
        {
            std::string result = PropertyType_attribs<T>::glsl_value(vec[0]);
            for (int i = 1; i < size; i++)
                result += ", " + PropertyType_attribs<T>::glsl_value(vec[i]);
            return result;
        }
        template<int rows, int cols, typename T>
        std::string MatrixArgumentsString(Matrix<rows, cols, T> mat)
        {
            std::string result = PropertyType_attribs<T>::glsl_value(mat[0][0]);
            for (int r = 0; r < rows; r++)
                for (int c = 0; c < cols; c++)
                    if (r != 0 || c != 0)
                        result += ", " + PropertyType_attribs<T>::glsl_value(mat[r][c]);
            return result;
        }
#pragma endregion

#pragma region primitive
        std::string PropertyType_attribs<bool>::glsl_name()
        {
            return "bool"s;
        }
        std::string PropertyType_attribs<bool>::glsl_value(const T &val)
        {
            return Util::ToString(val);
        }
        void PropertyType_attribs<bool>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1i(uniformLocation, val);
            checkForGlError();
        }

        std::string PropertyType_attribs<int>::glsl_name()
        {
            return "int"s;
        }
        std::string PropertyType_attribs<int>::glsl_value(const T &val)
        {
            return Util::ToString(val);
        }
        void PropertyType_attribs<int>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1i(uniformLocation, val);
            checkForGlError();
        }

        std::string PropertyType_attribs<unsigned>::glsl_name()
        {
            return "uint"s;
        }
        std::string PropertyType_attribs<unsigned>::glsl_value(const T &val)
        {
            return Util::ToString(val);
        }
        void PropertyType_attribs<unsigned>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1ui(uniformLocation, val);
            checkForGlError();
        }

        std::string PropertyType_attribs<float>::glsl_name()
        {
            return "float"s;
        }
        std::string PropertyType_attribs<float>::glsl_value(const T &val)
        {
            return Util::ToString(val);
        }
        void PropertyType_attribs<float>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1f(uniformLocation, val);
            checkForGlError();
        }

        std::string PropertyType_attribs<double>::glsl_name()
        {
            return "double"s;
        }
        std::string PropertyType_attribs<double>::glsl_value(const T &val)
        {
            return Util::ToString(val);
        }
        void PropertyType_attribs<double>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1d(uniformLocation, val);
            checkForGlError();
        }
#pragma endregion

#pragma region bvec
        std::string PropertyType_attribs<Vector<2, bool>>::glsl_name()
        {
            return "bvec2"s;
        }
        std::string PropertyType_attribs<Vector<2, bool>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<2, bool>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }

        std::string PropertyType_attribs<Vector<3, bool>>::glsl_name()
        {
            return "bvec3"s;
        }
        std::string PropertyType_attribs<Vector<3, bool>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<3, bool>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }

        std::string PropertyType_attribs<Vector<4, bool>>::glsl_name()
        {
            return "bvec4"s;
        }
        std::string PropertyType_attribs<Vector<4, bool>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<4, bool>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
#pragma endregion

#pragma region ivec
        std::string PropertyType_attribs<Vector<2, int>>::glsl_name()
        {
            return "ivec2"s;
        }
        std::string PropertyType_attribs<Vector<2, int>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<2, int>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform2i(uniformLocation, val[0], val[1]);
            checkForGlError();
        }

        std::string PropertyType_attribs<Vector<3, int>>::glsl_name()
        {
            return "ivec3"s;
        }
        std::string PropertyType_attribs<Vector<3, int>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<3, int>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform3i(uniformLocation, val[0], val[1], val[2]);
            checkForGlError();
        }

        std::string PropertyType_attribs<Vector<4, int>>::glsl_name()
        {
            return "ivec4"s;
        }
        std::string PropertyType_attribs<Vector<4, int>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<4, int>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform4i(uniformLocation, val[0], val[1], val[2], val[3]);
            checkForGlError();
        }
#pragma endregion

#pragma region uvec
        std::string PropertyType_attribs<Vector<2, unsigned>>::glsl_name()
        {
            return "uvec2"s;
        }
        std::string PropertyType_attribs<Vector<2, unsigned>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<2, unsigned>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform2ui(uniformLocation, val[0], val[1]);
            checkForGlError();
        }

        std::string PropertyType_attribs<Vector<3, unsigned>>::glsl_name()
        {
            return "uvec3"s;
        }
        std::string PropertyType_attribs<Vector<3, unsigned>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<3, unsigned>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform3ui(uniformLocation, val[0], val[1], val[2]);
            checkForGlError();
        }

        std::string PropertyType_attribs<Vector<4, unsigned>>::glsl_name()
        {
            return "uvec4"s;
        }
        std::string PropertyType_attribs<Vector<4, unsigned>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<4, unsigned>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform4ui(uniformLocation, val[0], val[1], val[2], val[3]);
            checkForGlError();
        }
#pragma endregion

#pragma region vec
        std::string PropertyType_attribs<Vector<2>>::glsl_name()
        {
            return "vec2"s;
        }
        std::string PropertyType_attribs<Vector<2>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<2>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            checkForGlError();
            glUniform2f(uniformLocation, val[0], val[1]);
            checkForGlError();
        }

        std::string PropertyType_attribs<Vector<3>>::glsl_name()
        {
            return "vec3"s;
        }
        std::string PropertyType_attribs<Vector<3>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<3>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform3f(uniformLocation, val[0], val[1], val[2]);
            checkForGlError();
        }

        std::string PropertyType_attribs<Vector<4>>::glsl_name()
        {
            return "vec4"s;
        }
        std::string PropertyType_attribs<Vector<4>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<4>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform4f(uniformLocation, val[0], val[1], val[2], val[3]);
            checkForGlError();
        }
#pragma endregion

#pragma region dvec
        std::string PropertyType_attribs<Vector<2, double>>::glsl_name()
        {
            return "dvec2"s;
        }
        std::string PropertyType_attribs<Vector<2, double>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<2, double>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform2d(uniformLocation, val[0], val[1]);
            checkForGlError();
        }

        std::string PropertyType_attribs<Vector<3, double>>::glsl_name()
        {
            return "dvec3"s;
        }
        std::string PropertyType_attribs<Vector<3, double>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<3, double>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform3d(uniformLocation, val[0], val[1], val[2]);
            checkForGlError();
        }
        constexpr unsigned PropertyType_attribs<Vector<3, double>>::glsl_attribute_size()
        {
            return 2;
        }

        std::string PropertyType_attribs<Vector<4, double>>::glsl_name()
        {
            return "dvec4"s;
        }
        std::string PropertyType_attribs<Vector<4, double>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Vector<4, double>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform4d(uniformLocation, val[0], val[1], val[2], val[3]);
            checkForGlError();
        }
        constexpr unsigned PropertyType_attribs<Vector<4, double>>::glsl_attribute_size()
        {
            return 2;
        }
#pragma endregion

#pragma region mat
        std::string PropertyType_attribs<Matrix<2, 2>>::glsl_name()
        {
            return "mat2"s;
        }
        std::string PropertyType_attribs<Matrix<2, 2>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<2, 2>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniformMatrix2fv(uniformLocation, 1, false, val.getAddr());
            checkForGlError();
        }
        constexpr unsigned PropertyType_attribs<Matrix<2, 2>>::glsl_attribute_size()
        {
            return 2;
        }

        std::string PropertyType_attribs<Matrix<2, 3>>::glsl_name()
        {
            return "mat2x3"s;
        }
        std::string PropertyType_attribs<Matrix<2, 3>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<2, 3>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        constexpr unsigned PropertyType_attribs<Matrix<2, 3>>::glsl_attribute_size()
        {
            return 3;
        }

        std::string PropertyType_attribs<Matrix<2, 4>>::glsl_name()
        {
            return "mat2x4"s;
        }
        std::string PropertyType_attribs<Matrix<2, 4>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<2, 4>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        constexpr unsigned PropertyType_attribs<Matrix<2, 4>>::glsl_attribute_size()
        {
            return 4;
        }

        std::string PropertyType_attribs<Matrix<3, 2>>::glsl_name()
        {
            return "mat3x2"s;
        }
        std::string PropertyType_attribs<Matrix<3, 2>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<3, 2>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        constexpr unsigned PropertyType_attribs<Matrix<3, 2>>::glsl_attribute_size()
        {
            return 2;
        }

        std::string PropertyType_attribs<Matrix<3, 3>>::glsl_name()
        {
            return "mat3"s;
        }
        std::string PropertyType_attribs<Matrix<3, 3>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<3, 3>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniformMatrix3fv(uniformLocation, 1, false, val.getAddr());
            checkForGlError();
        }
        constexpr unsigned PropertyType_attribs<Matrix<3, 3>>::glsl_attribute_size()
        {
            return 3;
        }

        std::string PropertyType_attribs<Matrix<3, 4>>::glsl_name()
        {
            return "mat3x4"s;
        }
        std::string PropertyType_attribs<Matrix<3, 4>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<3, 4>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        constexpr unsigned PropertyType_attribs<Matrix<3, 4>>::glsl_attribute_size()
        {
            return 4;
        }

        std::string PropertyType_attribs<Matrix<4, 2>>::glsl_name()
        {
            return "mat4x2"s;
        }
        std::string PropertyType_attribs<Matrix<4, 2>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<4, 2>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        constexpr unsigned PropertyType_attribs<Matrix<4, 2>>::glsl_attribute_size()
        {
            return 2;
        }

        std::string PropertyType_attribs<Matrix<4, 3>>::glsl_name()
        {
            return "mat4x3"s;
        }
        std::string PropertyType_attribs<Matrix<4, 3>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<4, 3>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        constexpr unsigned PropertyType_attribs<Matrix<4, 3>>::glsl_attribute_size()
        {
            return 3;
        }

        std::string PropertyType_attribs<Matrix<4, 4>>::glsl_name()
        {
            return "mat4"s;
        }
        std::string PropertyType_attribs<Matrix<4, 4>>::glsl_value(const T &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        void PropertyType_attribs<Matrix<4, 4>>::set_glsl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniformMatrix4fv(uniformLocation, 1, true, val.getAddr());
            checkForGlError();
        }
        constexpr unsigned PropertyType_attribs<Matrix<4, 4>>::glsl_attribute_size()
        {
            return 4;
        }
#pragma endregion

#pragma region advanced
        std::string PropertyType_attribs<Texture*>::glsl_name()
        {
            return "sampler2D"s;
        }
        void PropertyType_attribs<Texture*>::set_glsl_uniform(unsigned uniformLocation, const T &value)
        {
            assert(value->isReady());
            glUniform1i(uniformLocation, value->glslTextureLocation());
            checkForGlError();
        }
        constexpr PropertyFlag PropertyType_attribs<Texture*>::default_property_flags()
        {
            return PropertyFlag::Readonly;
        }

        std::string PropertyType_attribs<Subroutine*>::glsl_name()
        {
            return "***NOT IMPLEMENTED***"s;
        }
        void PropertyType_attribs<Subroutine*>::set_glsl_uniform(unsigned uniformLocation, const T &value)
        {
            uniformLocation; //TODO: What gives? Where do I use this?
            unsigned sr_loc = value->glslSubroutineLocation();
            glUniformSubroutinesuiv(GL_FRAGMENT_SHADER, 1, &sr_loc);
            checkForGlError();
        }
        constexpr PropertyFlag PropertyType_attribs<Subroutine*>::default_property_flags()
        {
            return PropertyFlag::Readonly;
        }
#pragma endregion
    }
}
