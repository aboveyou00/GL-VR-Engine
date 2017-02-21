#include "stdafx.h"
#include "EmptyGraphicsObject.h"

namespace GlEngine
{
    EmptyGraphicsObject::EmptyGraphicsObject()
        : GraphicsObject("EmptyGraphicsObject")
    {
    }
    EmptyGraphicsObject::~EmptyGraphicsObject()
    {
    }

    bool EmptyGraphicsObject::isReady()
    {
        return true;
    }

    void EmptyGraphicsObject::BuildVao(VaoFactory&)
    {
    }
    void EmptyGraphicsObject::RenderInstancedImpl(RenderTargetLayer, unsigned)
    {
    }

    void EmptyGraphicsObject::RenderImpl(RenderTargetLayer)
    {
    }
}
