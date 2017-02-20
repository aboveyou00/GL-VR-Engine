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

    std::string EmptyGraphicsObject::name()
    {
        return "EmptyGraphicsObject";
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
