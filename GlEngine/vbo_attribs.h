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

        inline static int check_whole_cache(T val, TArgs... others, std::vector<el_type> &values)
        {
            auto numElements = values.size() / element_count;
            for (size_t q = 0; q < numElements; q++)
            {
                if (check_cache(q * element_count, val, others..., values))
                    return q;
            }
            return -1;
        }
        inline static bool check_cache(unsigned offset, T val, TArgs... others, std::vector<el_type> &values)
        {
            if (!vbo_attribs<type, T>::check_cache(offset, val, values)) return false;
            return compound_vbo_attribs<type, TArgs...>::check_cache(offset + vbo_attribs<type, T>::element_count, others..., values);
        }

        static const unsigned attrib_count = vbo_attribs<type, T>::attrib_count + compound_vbo_attribs<type, TArgs...>::attrib_count;
        template <unsigned attribCount = attrib_count, unsigned idx = 0, unsigned start = 0>
        inline static void add_attribs(UnsafeVboFactory<type, attribCount> &factory)
        {
            vbo_attribs<type, T>::add_attribs<attribCount, idx, start>(factory);
            static const unsigned single_attr_count = vbo_attribs<type, T>::attrib_count;
            static const unsigned elCount = vbo_attribs<type, T>::element_count;
            compound_vbo_attribs<type, TArgs...>::add_attribs<attribCount, idx + single_attr_count, start + (elCount * sizeof(el_type))>(factory);
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
        inline static bool check_cache(unsigned, std::vector<el_type>&)
        {
            return true;
        }
        template <unsigned attribCount, unsigned idx, unsigned start>
        inline static void add_attribs(UnsafeVboFactory<type, attribCount>&)
        {
        }
    };

    template <VboType type>
    struct vbo_attribs<type, typename vbo_type_attribs<type>::type>
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        static const unsigned element_count = 1;
        inline static void push(const el_type &val, std::vector<el_type> &values)
        {
            values.push_back(val);
        }
        inline static bool check_cache(unsigned offset, el_type val, std::vector<el_type> &values)
        {
            return (values[offset] == val);
        }

        static const unsigned attrib_count = 1;
        template <unsigned attribCount, unsigned idx, unsigned start>
        inline static void add_attribs(UnsafeVboFactory<type, attribCount> &factory)
        {
            factory.AddAttrib(idx, start, 1);
        }
    };

    template <>
    struct vbo_attribs<VboType::Double, float>
    {
        static const unsigned element_count = 1;
        inline static void push(const float &val, std::vector<double> &values)
        {
            values.push_back((double)val);
        }
        inline static bool check_cache(unsigned offset, const float &val, std::vector<double> &values)
        {
            return (values[offset] == val);
        }

        static const unsigned attrib_count = 1;
        template <unsigned attribCount, unsigned idx, unsigned start>
        inline static void add_attribs(UnsafeVboFactory<VboType::Double, attribCount> &factory)
        {
            factory.AddAttrib(idx, start, 1);
        }
    };
}
