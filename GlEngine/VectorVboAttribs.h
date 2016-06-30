#pragma once

#include "Vector.h"

namespace GlEngine
{
    template <int dimension>
    struct vbo_attribs<VboType::Float, Vector<dimension>>
    {
        static const unsigned element_count = dimension;
        inline static void push(const Vector<dimension> &val, std::vector<float> &values)
        {
            for (size_t q = 0; q < dimension; q++)
            {
                values.push_back(val[q]);
            }
        }
    };
}
