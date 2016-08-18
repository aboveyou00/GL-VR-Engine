#include "stdafx.h"
#include "VboGraphicsObject.h"

namespace GlEngine
{
    VboGraphicsObject<>::VboGraphicsObject()
        : VboGraphicsObject(VaObject())
    {
    }
    VboGraphicsObject<>::VboGraphicsObject(VaObject vao)
        : Impl::VboGraphicsObjectImpl(vao, false)
    {
    }
    VboGraphicsObject<>::~VboGraphicsObject()
    {
    }

    const char *VboGraphicsObject<>::name()
    {
        return "VboGraphicsObject";
    }
}
