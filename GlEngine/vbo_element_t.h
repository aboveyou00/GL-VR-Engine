#pragma once
#include "VboType.h"
#include "VboFactory.h"

namespace GlEngine
{
    constexpr VboType ElementVboFactoryVboType = VboType::UnsignedInt;
    typedef vbo_type_attribs<ElementVboFactoryVboType>::type array_index_t;
    using ElementVboFactory = VboFactory<ElementVboFactoryVboType, array_index_t, array_index_t, array_index_t>;
}
