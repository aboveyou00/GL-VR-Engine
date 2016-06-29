#pragma once

#include "UnsafeVboFactory.h"
#include "vbo_attribs.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory : private UnsafeVboFactory<type, compound_vbo_attribs<type, TArgs...>::attrib_count>
    {
    public:
        VboFactory(BufferMode mode)
            : UnsafeVboFactory(compound_vbo_attribs<type, TArgs...>::element_count, mode)
        {
            compound_vbo_attribs<type, TArgs...>::add_attribs(*this);
        }
        ~VboFactory()
        {
        }

        void Allocate(unsigned vertexCount)
        {
            UnsafeVboFactory::Allocate(vertexCount);
        }

        void AddVertex(TArgs... args)
        {
            compound_vbo_attribs<type, TArgs...>::push(args..., data);
        }

        VbObject Compile()
        {
            return UnsafeVboFactory::Compile();
        }
    };
}
