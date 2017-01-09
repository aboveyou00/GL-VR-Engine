#pragma once

namespace GlEngine
{
    namespace ShaderFactory
    {
        template <typename T>
        struct PropertyType_attribs;

#pragma region primitive
        template <>
        struct PropertyType_attribs<bool>
        {
            typedef bool T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<int>
        {
            typedef int T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<unsigned>
        {
            typedef unsigned T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<float>
        {
            typedef float T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<double>
        {
            typedef double T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };
#pragma endregion

#pragma region bvec
        template <>
        struct PropertyType_attribs<Vector<2, bool>>
        {
            typedef Vector<2, bool> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<3, bool>>
        {
            typedef Vector<3, bool> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<4, bool>>
        {
            typedef Vector<4, bool> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };
#pragma endregion

#pragma region ivec
        template <>
        struct PropertyType_attribs<Vector<2, int>>
        {
            typedef Vector<2, int> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<3, int>>
        {
            typedef Vector<3, int> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<4, int>>
        {
            typedef Vector<4, int> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };
#pragma endregion

#pragma region uvec
        template <>
        struct PropertyType_attribs<Vector<2, unsigned>>
        {
            typedef Vector<2, unsigned> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<3, unsigned>>
        {
            typedef Vector<3, unsigned> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<4, unsigned>>
        {
            typedef Vector<4, unsigned> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };
#pragma endregion

#pragma region vec
        template <>
        struct PropertyType_attribs<Vector<2>>
        {
            typedef Vector<2> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<3>>
        {
            typedef Vector<3> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<4>>
        {
            typedef Vector<4> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };
#pragma endregion

#pragma region dvec
        template <>
        struct PropertyType_attribs<Vector<2, double>>
        {
            typedef Vector<2, double> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<3, double>>
        {
            typedef Vector<3, double> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Vector<4, double>>
        {
            typedef Vector<4, double> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };
#pragma endregion

#pragma region mat
        template <>
        struct PropertyType_attribs<Matrix<2, 2>>
        {
            typedef Matrix<2, 2> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Matrix<2, 3>>
        {
            typedef Matrix<2, 3> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Matrix<2, 4>>
        {
            typedef Matrix<2, 4> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Matrix<3, 2>>
        {
            typedef Matrix<3, 2> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Matrix<3, 3>>
        {
            typedef Matrix<3, 3> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Matrix<3, 4>>
        {
            typedef Matrix<3, 4> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Matrix<4, 2>>
        {
            typedef Matrix<4, 2> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Matrix<4, 3>>
        {
            typedef Matrix<4, 3> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };

        template <>
        struct PropertyType_attribs<Matrix<4, 4>>
        {
            typedef Matrix<4, 4> T;
            static const std::string glsl_name;
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
        };
#pragma endregion

        //TODO: sampler
    }
}
