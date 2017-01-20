#include "stdafx.h"
#include "PropertyType_attribs.h"

#include "StringUtils.h"

#include "OpenGl.h"

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
        std::string PropertyType_attribs<int>::glsl_name()
        {
            return "int"s;
        }
        std::string PropertyType_attribs<unsigned>::glsl_name()
        {
            return "uint"s;
        }
        std::string PropertyType_attribs<float>::glsl_name()
        {
            return "float"s;
        }
        std::string PropertyType_attribs<double>::glsl_name()
        {
            return "double"s;
        }

        std::string PropertyType_attribs<bool>::glsl_value(const bool &val)
        {
            return Util::ToString(val);
        }
        std::string PropertyType_attribs<int>::glsl_value(const int &val)
        {
            return Util::ToString(val);
        }
        std::string PropertyType_attribs<unsigned>::glsl_value(const unsigned &val)
        {
            return Util::ToString(val);
        }
        std::string PropertyType_attribs<float>::glsl_value(const float &val)
        {
            return Util::ToString(val);
        }
        std::string PropertyType_attribs<double>::glsl_value(const double &val)
        {
            return Util::ToString(val);
        }

        void PropertyType_attribs<bool>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        void PropertyType_attribs<int>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1i(uniformLocation, val);
        }
        void PropertyType_attribs<unsigned>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1ui(uniformLocation, val);
        }
        void PropertyType_attribs<float>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1f(uniformLocation, val);
        }
        void PropertyType_attribs<double>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform1d(uniformLocation, val);
        }
#pragma endregion

#pragma region bvec
        std::string PropertyType_attribs<Vector<2, bool>>::glsl_name()
        {
            return "bvec2"s;
        }
        std::string PropertyType_attribs<Vector<3, bool>>::glsl_name()
        {
            return "bvec3"s;
        }
        std::string PropertyType_attribs<Vector<4, bool>>::glsl_name()
        {
            return "bvec4"s;
        }

        std::string PropertyType_attribs<Vector<2, bool>>::glsl_value(const Vector<2, bool> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<3, bool>>::glsl_value(const Vector<3, bool> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<4, bool>>::glsl_value(const Vector<4, bool> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }

        void PropertyType_attribs<Vector<2, bool>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        void PropertyType_attribs<Vector<3, bool>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        void PropertyType_attribs<Vector<4, bool>>::set_gl_uniform(unsigned uniformLocation, const T &val)
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
        std::string PropertyType_attribs<Vector<3, int>>::glsl_name()
        {
            return "ivec3"s;
        }
        std::string PropertyType_attribs<Vector<4, int>>::glsl_name()
        {
            return "ivec4"s;
        }

        std::string PropertyType_attribs<Vector<2, int>>::glsl_value(const Vector<2, int> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<3, int>>::glsl_value(const Vector<3, int> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<4, int>>::glsl_value(const Vector<4, int> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }

        void PropertyType_attribs<Vector<2, int>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform2i(uniformLocation, val[0], val[1]);
        }
        void PropertyType_attribs<Vector<3, int>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform3i(uniformLocation, val[0], val[1], val[2]);
        }
        void PropertyType_attribs<Vector<4, int>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform4i(uniformLocation, val[0], val[1], val[2], val[3]);
        }
#pragma endregion

#pragma region uvec
        std::string PropertyType_attribs<Vector<2, unsigned>>::glsl_name()
        {
            return "uvec2"s;
        }
        std::string PropertyType_attribs<Vector<3, unsigned>>::glsl_name()
        {
            return "uvec3"s;
        }
        std::string PropertyType_attribs<Vector<4, unsigned>>::glsl_name()
        {
            return "uvec4"s;
        }

        std::string PropertyType_attribs<Vector<2, unsigned>>::glsl_value(const Vector<2, unsigned> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<3, unsigned>>::glsl_value(const Vector<3, unsigned> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<4, unsigned>>::glsl_value(const Vector<4, unsigned> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }

        void PropertyType_attribs<Vector<2, unsigned>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform2ui(uniformLocation, val[0], val[1]);
        }
        void PropertyType_attribs<Vector<3, unsigned>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform3ui(uniformLocation, val[0], val[1], val[2]);
        }
        void PropertyType_attribs<Vector<4, unsigned>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform4ui(uniformLocation, val[0], val[1], val[2], val[3]);
        }
#pragma endregion

#pragma region vec
        std::string PropertyType_attribs<Vector<2>>::glsl_name()
        {
            return "vec2"s;
        }
        std::string PropertyType_attribs<Vector<3>>::glsl_name()
        {
            return "vec3"s;
        }
        std::string PropertyType_attribs<Vector<4>>::glsl_name()
        {
            return "vec4"s;
        }

        std::string PropertyType_attribs<Vector<2>>::glsl_value(const Vector<2> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<3>>::glsl_value(const Vector<3> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<4>>::glsl_value(const Vector<4> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }

        void PropertyType_attribs<Vector<2>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform2f(uniformLocation, val[0], val[1]);
        }
        void PropertyType_attribs<Vector<3>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform3f(uniformLocation, val[0], val[1], val[2]);
        }
        void PropertyType_attribs<Vector<4>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform4f(uniformLocation, val[0], val[1], val[2], val[3]);
        }
#pragma endregion

#pragma region dvec
        std::string PropertyType_attribs<Vector<2, double>>::glsl_name()
        {
            return "dvec2"s;
        }
        std::string PropertyType_attribs<Vector<3, double>>::glsl_name()
        {
            return "dvec3"s;
        }
        std::string PropertyType_attribs<Vector<4, double>>::glsl_name()
        {
            return "dvec4"s;
        }

        std::string PropertyType_attribs<Vector<2, double>>::glsl_value(const Vector<2, double> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<3, double>>::glsl_value(const Vector<3, double> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Vector<4, double>>::glsl_value(const Vector<4, double> &val)
        {
            return glsl_name() + "(" + VectorArgumentsString(val) + ")";
        }

        void PropertyType_attribs<Vector<2, double>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform2d(uniformLocation, val[0], val[1]);
        }
        void PropertyType_attribs<Vector<3, double>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform3d(uniformLocation, val[0], val[1], val[2]);
        }
        void PropertyType_attribs<Vector<4, double>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniform4d(uniformLocation, val[0], val[1], val[2], val[3]);
        }
#pragma endregion

#pragma region mat
        std::string PropertyType_attribs<Matrix<2, 2>>::glsl_name()
        {
            return "mat2"s;
        }
        std::string PropertyType_attribs<Matrix<2, 3>>::glsl_name()
        {
            return "mat2x3"s;
        }
        std::string PropertyType_attribs<Matrix<2, 4>>::glsl_name()
        {
            return "mat2x4"s;
        }

        std::string PropertyType_attribs<Matrix<3, 2>>::glsl_name()
        {
            return "mat3x2"s;
        }
        std::string PropertyType_attribs<Matrix<3, 3>>::glsl_name()
        {
            return "mat3"s;
        }
        std::string PropertyType_attribs<Matrix<3, 4>>::glsl_name()
        {
            return "mat3x4"s;
        }

        std::string PropertyType_attribs<Matrix<4, 2>>::glsl_name()
        {
            return "mat4x2"s;
        }
        std::string PropertyType_attribs<Matrix<4, 3>>::glsl_name()
        {
            return "mat4x3"s;
        }
        std::string PropertyType_attribs<Matrix<4, 4>>::glsl_name()
        {
            return "mat4"s;
        }

        std::string PropertyType_attribs<Matrix<2, 2>>::glsl_value(const Matrix<2, 2> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Matrix<2, 3>>::glsl_value(const Matrix<2, 3> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Matrix<2, 4>>::glsl_value(const Matrix<2, 4> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }

        std::string PropertyType_attribs<Matrix<3, 2>>::glsl_value(const Matrix<3, 2> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Matrix<3, 3>>::glsl_value(const Matrix<3, 3> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Matrix<3, 4>>::glsl_value(const Matrix<3, 4> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }

        std::string PropertyType_attribs<Matrix<4, 2>>::glsl_value(const Matrix<4, 2> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Matrix<4, 3>>::glsl_value(const Matrix<4, 3> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }
        std::string PropertyType_attribs<Matrix<4, 4>>::glsl_value(const Matrix<4, 4> &val)
        {
            return glsl_name() + "(" + MatrixArgumentsString(val) + ")";
        }

        void PropertyType_attribs<Matrix<2, 2>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniformMatrix2fv(uniformLocation, 1, false, val.getAddr());
        }
        void PropertyType_attribs<Matrix<2, 3>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        void PropertyType_attribs<Matrix<2, 4>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }

        void PropertyType_attribs<Matrix<3, 2>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        void PropertyType_attribs<Matrix<3, 3>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniformMatrix3fv(uniformLocation, 1, false, val.getAddr());
        }
        void PropertyType_attribs<Matrix<3, 4>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }

        void PropertyType_attribs<Matrix<4, 2>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        void PropertyType_attribs<Matrix<4, 3>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            uniformLocation; val;
            assert(false);
        }
        void PropertyType_attribs<Matrix<4, 4>>::set_gl_uniform(unsigned uniformLocation, const T &val)
        {
            glUniformMatrix4fv(uniformLocation, 1, false, val.getAddr());
        }
#pragma endregion

#pragma region advanced
        std::string PropertyType_attribs<Texture*>::glsl_name()
        {
            return "sampler2d"s;
        }

        void PropertyType_attribs<Texture*>::set_gl_uniform(unsigned uniformLocation, const T &value)
        {
            uniformLocation; value;
            assert(false);
        }

        //template <>
        //template <typename... TArgs>
        //struct ENGINE_SHARED PropertyType_attribs<Struct<TArgs...>>
        //{
        //    typedef Struct<TArgs...> T;
        //    static std::string glsl_name();
        //    static void set_gl_uniform(unsigned uniformLocation, const T &value);
        //};

        //template <>
        //template <typename TElem, unsigned size>
        //struct ENGINE_SHARED PropertyType_attribs<Array<TElem, size>>
        //{
        //    typedef Array<TElem, size> T;
        //    static std::string glsl_name();
        //    static void set_gl_uniform(unsigned uniformLocation, const T &value);
        //};
#pragma endregion
    }
}
