#include "stdafx.h"
#include "EmptyGraphicsObject.h"

namespace GlEngine
{
    EmptyGraphicsObject::EmptyGraphicsObject()
    {
    }
    EmptyGraphicsObject::~EmptyGraphicsObject()
    {
    }

    const char *EmptyGraphicsObject::name()
    {
        return "EmptyGraphicsObject";
    }
    EmptyGraphicsObject::operator bool()
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
