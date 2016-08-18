#pragma once

#include "Matrix.h"

namespace GlEngine
{
    template <VboType type, int dimension>
    struct vbo_attribs<type, Matrix<dimension, dimension, typename vbo_type_attribs<type>::type>>
    {
    private:
        typedef typename vbo_type_attribs<type>::type el_type;

    public:
        static const unsigned element_count = dimension * dimension;
        inline static void push(const Matrix<dimension, dimension, el_type> &val, std::vector<el_type> &values)
        {
            for (size_t q = 0; q < dimension; q++)
                for (size_t w = 0; w < dimension; w++)
                    vbo_attribs<type, el_type>::push(val[q][w], values);
        }

        inline static bool check_cache(unsigned offset, const Matrix<dimension, dimension, el_type> &val, std::vector<el_type> &values)
        {
            for (size_t q = 0; q < dimension; q++)
                for (size_t w = 0; w < dimension; w++)
                    if (values[offset + (q * dimension) + w] != val[q][w])
                        return false;
            return true;
        }
    };
}
