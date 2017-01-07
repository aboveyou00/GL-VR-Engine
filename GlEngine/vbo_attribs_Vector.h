#pragma once

#include "Vector.h"

namespace GlEngine
{
    template <VboType type, int dimension>
    struct vbo_attribs<type, Vector<dimension, typename vbo_type_attribs<type>::type>>
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        static const unsigned element_count = dimension;
        inline static void push(const Vector<dimension, el_type> &val, std::vector<el_type> &values)
        {
            for (size_t q = 0; q < dimension; q++)
                vbo_attribs<type, el_type>::push(val[q], values);
        }

        inline static bool check_cache(unsigned offset, const Vector<dimension, el_type> &val, std::vector<el_type> &values)
        {
            for (size_t q = 0; q < dimension; q++)
                if (values[offset + q] != val[q])
                    return false;
            return true;
        }

        static const unsigned attrib_count = 1;
        template <unsigned attribCount, unsigned idx, unsigned start>
        inline static void add_attribs(UnsafeVboFactory<type, attribCount> &factory)
        {
            static_assert(dimension <= 4, "You can't use a Vector with more than 4 as it's size in OpenGL!");
            factory.AddAttrib(idx, start, dimension);
        }
    };
}
