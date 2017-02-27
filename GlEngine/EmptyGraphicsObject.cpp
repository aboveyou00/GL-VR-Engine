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
    void EmptyGraphicsObject::RenderInstancedImpl(RenderStage*, unsigned)
    {
    }

    void EmptyGraphicsObject::RenderImpl(RenderStage*)
    {
    }
}
