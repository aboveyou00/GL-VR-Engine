#pragma once

#include "Struct.h"
#include "Array.h"
#include <sstream>
#include "PropertyFlag.h"

namespace GlEngine
{
    class Texture;

    namespace ShaderFactory
    {
        template <typename T>
        struct PropertyType_attribs;

#pragma region primitive
        template <>
        struct ENGINE_SHARED PropertyType_attribs<bool>
        {
            typedef bool T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<int>
        {
            typedef int T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<unsigned>
        {
            typedef unsigned T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<float>
        {
            typedef float T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<double>
        {
            typedef double T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };
#pragma endregion

#pragma region bvec
        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<2, bool>>
        {
            typedef Vector<2, bool> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<3, bool>>
        {
            typedef Vector<3, bool> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<4, bool>>
        {
            typedef Vector<4, bool> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };
#pragma endregion

#pragma region ivec
        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<2, int>>
        {
            typedef Vector<2, int> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<3, int>>
        {
            typedef Vector<3, int> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<4, int>>
        {
            typedef Vector<4, int> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };
#pragma endregion

#pragma region uvec
        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<2, unsigned>>
        {
            typedef Vector<2, unsigned> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<3, unsigned>>
        {
            typedef Vector<3, unsigned> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<4, unsigned>>
        {
            typedef Vector<4, unsigned> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };
#pragma endregion

#pragma region vec
        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<2>>
        {
            typedef Vector<2> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<3>>
        {
            typedef Vector<3> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<4>>
        {
            typedef Vector<4> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };
#pragma endregion

#pragma region dvec
        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<2, double>>
        {
            typedef Vector<2, double> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<3, double>>
        {
            typedef Vector<3, double> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Vector<4, double>>
        {
            typedef Vector<4, double> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };
#pragma endregion

#pragma region mat
        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<2, 2>>
        {
            typedef Matrix<2, 2> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<2, 3>>
        {
            typedef Matrix<2, 3> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<2, 4>>
        {
            typedef Matrix<2, 4> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<3, 2>>
        {
            typedef Matrix<3, 2> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<3, 3>>
        {
            typedef Matrix<3, 3> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<3, 4>>
        {
            typedef Matrix<3, 4> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<4, 2>>
        {
            typedef Matrix<4, 2> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<4, 3>>
        {
            typedef Matrix<4, 3> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };

        template <>
        struct ENGINE_SHARED PropertyType_attribs<Matrix<4, 4>>
        {
            typedef Matrix<4, 4> T;
            static std::string glsl_name();
            static std::string glsl_value(const T &value);
            static void set_gl_uniform(unsigned uniformLocation, const T &value);
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = 1;
        };
#pragma endregion

#pragma region advanced
        template <>
        struct ENGINE_SHARED PropertyType_attribs<Texture*>
        {
            typedef Texture *T;
            static std::string glsl_name();
            static void set_gl_uniform(unsigned uniformLocation, const T &value, unsigned texIdx);
            static const PropertyFlag default_property_flags = PropertyFlag::Readonly;
            static const unsigned glsl_layout_size = 1;
        };

        template <typename... TArgs>
        struct PropertyType_attribs<Struct<TArgs...>>
        {
            typedef Struct<TArgs...> T;
            static const std::string glsl_name()
            {
                std::stringstream stream;
                stream << "struct {\n";
                unsigned idx = ;
                (stream << ... << (PropertyType_attribs<TArgs>::glsl_name() << idx++));
                stream << "}";
                return stream.str();
            }
            static void set_gl_uniform(unsigned uniformLocation, const T &value)
            {
                uniformLocation; value;
                static_assert((true && ... && (PropertyType_attribs<TArgs>::default_property_flags & PropertyFlag::Readonly) == PropertyFlag::None));
                assert(false);
            }
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = (0 + ... + PropertyType_attribs<TArgs>::glsl_layout_size);
        };

        template <typename TElem, unsigned size>
        struct PropertyType_attribs<Array<TElem, size>>
        {
            typedef Array<TElem, size> T;
            static std::string glsl_name()
            {
                std::stringstream stream;
                stream << PropertyType_attribs<TElem>::glsl_name();
                return stream.str();
            }
            static void set_gl_uniform(unsigned uniformLocation, const T &value)
            {
                uniformLocation; value;
                assert(false);
            }
            static const PropertyFlag default_property_flags = PropertyFlag::None;
            static const unsigned glsl_layout_size = size * PropertyType_attribs<TElem>::glsl_layout_size;
        };
        //template <typename TElem, unsigned size>
        //std::string Property<Array<TElem, size>>::DeclarationString(std::string prefix = "")
        //{
        //    std::stringstream stream;
        //    stream << PropertyType_attribs<Array<TElem, size>>::glsl_name() << " ";
        //    stream << prefix << name << "[" << size << "]";
        //    return stream.str();
        //}
#pragma endregion
    }
}
