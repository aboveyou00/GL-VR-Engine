#pragma once

#include "CompoundGraphicsObjectImpl.h"
#include "EmptyGraphicsObject.h"

namespace GlEngine
{
    template <unsigned elem_count>
    class CompoundGraphicsObject : public Impl::CompoundGraphicsObjectImpl
    {
    public:
        template <typename... TArgs>
        CompoundGraphicsObject(TArgs... args)
            : Impl::CompoundGraphicsObjectImpl(gobjs, elem_count)
        {
            ctor(args...);
        }
        ~CompoundGraphicsObject()
        {
        }

    private:
        TransformedGraphicsObject gobjs[elem_count];

        template <unsigned idx = 0, typename T, typename... TArgs>
        inline void ctor(T t, TArgs... args)
        {
            gobjs[idx] = (TransformedGraphicsObject)t;
            ctor<idx + 1, TArgs...>(args...);
        }
        template <unsigned idx = 0, typename T>
        inline void ctor(T t)
        {
            gobjs[idx] = (TransformedGraphicsObject)t;
            static_assert(idx + 1 == elem_count, "You must supply the correct number of arguments to the CompoundGraphicsObject constructor");
        }
    };

    template <>
    class ENGINE_SHARED CompoundGraphicsObject<0> : public EmptyGraphicsObject
    {
        CompoundGraphicsObject();
        ~CompoundGraphicsObject();
    };
}
