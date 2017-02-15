#pragma once

#include "Struct.h"
#include "Array.h"
#include "Subroutine.h"
#include <sstream>
#include "PropertyFlag.h"
#include "TemplateUtils.h"

namespace GlEngine
{
    class Texture;

    namespace ShaderFactory
    {
        template <typename TType>
        struct PropertyType_attribs
        {
            typedef TType T;
            static std::string glsl_name()
            {
                static_assert(false, "Invalid type parameter for PropertyType_attribs");
            }
            static void decl_string(std::stringstream &stream, std::string prefix, std::string name)
            {
                stream << PropertyType_attribs<T>::glsl_name() << " ";
                stream << prefix << name;
            }
            static std::string glsl_value(const T &value)
            {
                static_assert(false, "Invalid type parameter for PropertyType_attribs; or, this type parameter cannot be used to inject constant values");
            }
            static void set_glsl_uniform(unsigned uniformLocation, const T &value)
            {
                static_assert(false, "Invalid type parameter for PropertyType_attribs");
            }
            static constexpr PropertyFlag default_property_flags()
            {
                return PropertyFlag::None;
            }
            static constexpr unsigned glsl_uniform_size()
            {
                return 1;
            }
            static constexpr unsigned glsl_attribute_size()
            {
                return 1;
            }
        };

        template<typename ThisArg = void, typename... TArgs>
        struct compound_PropertyType_attribs
        {
            static constexpr unsigned glsl_uniform_size()
            {
                return PropertyType_attribs<ThisArg>::glsl_uniform_size() + compound_PropertyType_attribs<TArgs...>::glsl_uniform_size();
            }
            static constexpr unsigned glsl_attribute_size()
            {
                return PropertyType_attribs<ThisArg>::glsl_attribute_size() + compound_PropertyType_attribs<TArgs...>::glsl_attribute_size();
            }

            template <unsigned idx = 0>
            static void struct_decl(std::stringstream &stream)
            {
                stream << PropertyType_attribs<ThisArg>::glsl_name() << " v" << idx << "; ";
                compound_PropertyType_attribs<TArgs...>::struct_decl<idx + 1>(stream);
            }

            static void set_glsl_uniform(unsigned uniformIdx, ThisArg val, TArgs... otherVals)
            {
                PropertyType_attribs<ThisArg>::set_glsl_uniform(uniformIdx, val);
                compound_PropertyType_attribs<TArgs...>::set_glsl_uniform(uniformIdx + PropertyType_attribs<ThisArg>::glsl_uniform_size(), otherVals...);
            }
        };

        template <>
        struct compound_PropertyType_attribs<void>
        {
            static constexpr unsigned glsl_uniform_size()
            {
                return 0;
            }
            static constexpr unsigned glsl_attribute_size()
            {
                return 0;
            }
            template <unsigned idx = 0>
            static void struct_decl(std::stringstream&) { }
            static void set_glsl_uniform(unsigned) { }
        };

#pragma warning(disable: 4506)

#pragma region primitive
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<bool>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<bool>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<bool>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<int>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<int>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<int>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<unsigned>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<unsigned>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<unsigned>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<float>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<float>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<float>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<double>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<double>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<double>::set_glsl_uniform(unsigned uniformLocation, const T &value);
#pragma endregion

#pragma region bvec
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2, bool>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2, bool>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<2, bool>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3, bool>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3, bool>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<3, bool>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4, bool>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4, bool>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<4, bool>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
#pragma endregion

#pragma region ivec
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2, int>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2, int>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<2, int>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3, int>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3, int>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<3, int>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4, int>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4, int>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<4, int>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
#pragma endregion

#pragma region uvec
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2, unsigned>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2, unsigned>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<2, unsigned>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3, unsigned>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3, unsigned>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<3, unsigned>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4, unsigned>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4, unsigned>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<4, unsigned>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
#pragma endregion

#pragma region vec
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<2>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<3>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<4>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
#pragma endregion

#pragma region dvec
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2, double>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<2, double>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<2, double>>::set_glsl_uniform(unsigned uniformLocation, const T &value);

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3, double>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<3, double>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<3, double>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Vector<3, double>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4, double>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Vector<4, double>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Vector<4, double>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Vector<4, double>>::glsl_attribute_size();
#pragma endregion

#pragma region mat
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<2, 2>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<2, 2>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<2, 2>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<2, 2>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<2, 3>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<2, 3>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<2, 3>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<2, 3>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<2, 4>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<2, 4>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<2, 4>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<2, 4>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<3, 2>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<3, 2>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<3, 2>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<3, 2>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<3, 3>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<3, 3>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<3, 3>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<3, 3>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<3, 4>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<3, 4>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<3, 4>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<3, 4>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<4, 2>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<4, 2>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<4, 2>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<4, 2>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<4, 3>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<4, 3>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<4, 3>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<4, 3>>::glsl_attribute_size();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<4, 4>>::glsl_name();
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Matrix<4, 4>>::glsl_value(const T &value);
        template <>
        ENGINE_SHARED void PropertyType_attribs<Matrix<4, 4>>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr unsigned PropertyType_attribs<Matrix<4, 4>>::glsl_attribute_size();
#pragma endregion

#pragma region advanced
        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Texture*>::glsl_name();
        template <>
        ENGINE_SHARED void PropertyType_attribs<Texture*>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr PropertyFlag PropertyType_attribs<Texture*>::default_property_flags();

        template <>
        ENGINE_SHARED std::string PropertyType_attribs<Subroutine*>::glsl_name();
        template <>
        ENGINE_SHARED void PropertyType_attribs<Subroutine*>::set_glsl_uniform(unsigned uniformLocation, const T &value);
        template <>
        ENGINE_SHARED constexpr PropertyFlag PropertyType_attribs<Subroutine*>::default_property_flags();

        template <typename... TArgs>
        struct PropertyType_attribs<Struct<TArgs...>>
        {
            typedef Struct<TArgs...> T;
            static const std::string glsl_name()
            {
                std::stringstream stream;
                stream << "struct { ";
                //(stream << ... << (PropertyType_attribs<TArgs>::glsl_name() << idx++));
                compound_PropertyType_attribs<TArgs...>::struct_decl(stream);
                stream << "}";
                return stream.str();
            }
            static void decl_string(std::stringstream &stream, std::string prefix, std::string name)
            {
                stream << PropertyType_attribs<T>::glsl_name() << " ";
                stream << prefix << name;
            }
            static void set_glsl_uniform(unsigned uniformLocation, const T &value)
            {
                uniformLocation; value;
                //static_assert((true && ... && (PropertyType_attribs<TArgs>::default_property_flags() & PropertyFlag::Readonly) == PropertyFlag::None), "Structs cannot contain readonly property types! (Example: Texture*)");
                Util::call(compound_PropertyType_attribs<TArgs...>::set_glsl_uniform, value._tup, uniformLocation);
            }
            static constexpr PropertyFlag default_property_flags()
            {
                return PropertyFlag::None;
            }
            static constexpr unsigned glsl_uniform_size()
            {
                return compound_PropertyType_attribs<TArgs...>::glsl_uniform_size();
            }
            //static constexpr unsigned glsl_uniform_size()
            //{
            //    return (0 + ... + PropertyType_attribs<TArgs>::glsl_uniform_size());
            //}
            static constexpr unsigned glsl_attribute_size()
            {
                return compound_PropertyType_attribs<TArgs...>::glsl_attribute_size();
            }
        };

        //template <>
        //template <typename... TArgs>
        //const std::string PropertyType_attribs<Struct<TArgs...>>::glsl_name()
        //{
        //    std::stringstream stream;
        //    stream << "struct { ";
        //    //(stream << ... << (PropertyType_attribs<TArgs>::glsl_name() << idx++));
        //    compound_PropertyType_attribs<TArgs...>::struct_decl(stream);
        //    stream << "}";
        //    return stream.str();
        //}
        //template <>
        //template <typename... TArgs>
        //void PropertyType_attribs<Struct<TArgs...>>::set_glsl_uniform(unsigned uniformLocation, const T &value)
        //{
        //    uniformLocation; value;
        //    //static_assert((true && ... && (PropertyType_attribs<TArgs>::default_property_flags() & PropertyFlag::Readonly) == PropertyFlag::None), "Structs cannot contain readonly property types! (Example: Texture*)");
        //    Util::call(compound_PropertyType_attribs<TArgs...>::set_glsl_uniform, value._tup, uniformLocation);
        //}
        //template <>
        //template <typename... TArgs>
        //constexpr unsigned PropertyType_attribs<Struct<TArgs...>>::glsl_uniform_size()
        //{
        //    return compound_PropertyType_attribs<TArgs...>::glsl_uniform_size();
        //    //return (0 + ... + PropertyType_attribs<TArgs>::glsl_uniform_size());
        //}
        //template <>
        //template <typename... TArgs>
        //constexpr unsigned PropertyType_attribs<Struct<TArgs...>>::glsl_attribute_size()
        //{
        //    return compound_PropertyType_attribs<TArgs...>::glsl_attribute_size();
        //    //return (0 + ... + PropertyType_attribs<TArgs>::glsl_attribute_size());
        //}

        template <typename TElem, unsigned size_arr>
        struct PropertyType_attribs<Array<TElem, size_arr>>
        {
            typedef Array<TElem, size_arr> T;
            static std::string glsl_name()
            {
                return PropertyType_attribs<TElem>::glsl_name();
            }
            static void decl_string(std::stringstream &stream, std::string prefix, std::string name)
            {
                stream << PropertyType_attribs<T>::glsl_name() << " ";
                stream << prefix << name << "[" << size_arr << "]";
            }
            static void set_gl_uniform(unsigned uniformLocation, const T &value)
            {
                uniformLocation; value;
                assert(false);
            }
            static constexpr PropertyFlag default_property_flags()
            {
                return PropertyFlag::Array;
            }
            static constexpr unsigned glsl_uniform_size()
            {
                return size_arr * PropertyType_attribs<TElem>::glsl_uniform_size();
            }
            static constexpr unsigned glsl_attribute_size()
            {
                return size_arr * PropertyType_attribs<TElem>::glsl_attribute_size();
            }
        };
#pragma endregion
    }
}
