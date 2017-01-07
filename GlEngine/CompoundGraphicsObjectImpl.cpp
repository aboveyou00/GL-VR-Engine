#include "stdafx.h"
#include "CompoundGraphicsObject.h"

namespace GlEngine
{
    namespace Impl
    {
        CompoundGraphicsObjectImpl::CompoundGraphicsObjectImpl(TransformedGraphicsObject *t_gobjs, unsigned count)
            : GraphicsObject(false), t_gobjs(t_gobjs), count(count)
        {
        }
        CompoundGraphicsObjectImpl::~CompoundGraphicsObjectImpl()
        {
        }

        void CompoundGraphicsObjectImpl::BuildVao(VaoFactory&)
        {
            assert(false);
        }
        void CompoundGraphicsObjectImpl::RenderInstancedImpl(RenderTargetLayer, unsigned)
        {
            assert(false);
        }

        void CompoundGraphicsObjectImpl::RenderImpl(RenderTargetLayer layer)
        {
            for (size_t q = 0; q < count; q++)
                t_gobjs[q].Render(layer);
        }

        const char *CompoundGraphicsObjectImpl::name()
        {
            return "CompoundGraphicsObjectImpl";
        }
        CompoundGraphicsObjectImpl::operator bool()
        {
            for (size_t q = 0; q < count; q++)
                if (!t_gobjs[q]) return false;
            return true;
        }

        TransformedGraphicsObject &CompoundGraphicsObjectImpl::operator[](unsigned idx)
        {
            return t_gobjs[idx];
        }
        const TransformedGraphicsObject &CompoundGraphicsObjectImpl::operator[](unsigned idx) const
        {
            return t_gobjs[idx];
        }
    }
}
