#pragma once

#include "UnsafeVboFactory.h"
#include "VboType.h"

namespace GlEngine
{
    template <VboType type, typename T>
    struct vbo_attribs;

    template <VboType type, typename T = void, typename... TArgs>
    struct compound_vbo_attribs
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        static const unsigned element_count = vbo_attribs<type, T>::element_count + compound_vbo_attribs<type, TArgs...>::element_count;
        inline static void push(T val, TArgs... others, std::vector<el_type> &values)
        {
            vbo_attribs<type, T>::push(val, values);
            compound_vbo_attribs<type, TArgs...>::push(others..., values);
        }

        static const unsigned attrib_count = 1 + compound_vbo_attribs<type, TArgs...>::attrib_count;
        template <unsigned attribCount = attrib_count, unsigned idx = 0, unsigned start = 0>
        inline static void add_attribs(UnsafeVboFactory<type, attribCount> &factory)
        {
            static const unsigned elCount = vbo_attribs<type, T>::element_count;
            factory.AddAttrib(idx, start, elCount);
            compound_vbo_attribs<type, TArgs...>::add_attribs<attribCount, idx + 1, start + (elCount * sizeof(el_type))>(factory);
        }
    };

    template <VboType type>
    struct compound_vbo_attribs<type, void>
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        static const unsigned element_count = 0;
        static const unsigned attrib_count = 0;
        inline static void push(std::vector<el_type>&)
        {
        }
        template <unsigned attribCount = attrib_count, unsigned idx = 0, unsigned start = 0>
        inline static void add_attribs(UnsafeVboFactory<type, attribCount>&)
        {
        }
    };

    template <>
    struct vbo_attribs<VboType::Int, int32_t>
    {
        static const unsigned element_count = 1;
        inline static void push(const int32_t &val, std::vector<int> &values)
        {
            values.push_back(val);
        }
    };
    template <>
    struct vbo_attribs<VboType::UnsignedInt, uint32_t>
    {
        static const unsigned element_count = 1;
        inline static void push(const uint32_t &val, std::vector<uint32_t> &values)
        {
            values.push_back(val);
        }
    };

    template <>
    struct vbo_attribs<VboType::Float, float>
    {
        static const unsigned element_count = 1;
        inline static void push(const float &val, std::vector<float> &values)
        {
            values.push_back(val);
        }
    };

    template <>
    struct vbo_attribs<VboType::Double, float>
    {
        static const unsigned element_count = 1;
        inline static void push(const double &val, std::vector<double> &values)
        {
            values.push_back((double)val);
        }
    };
    template <>
    struct vbo_attribs<VboType::Double, double>
    {
        static const unsigned element_count = 1;
        inline static void push(const double &val, std::vector<double> &values)
        {
            values.push_back(val);
        }
    };
}
