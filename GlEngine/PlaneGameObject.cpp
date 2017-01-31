#include "stdafx.h"
#include "PlaneGameObject.h"

namespace GlEngine
{
    PlaneGameObject::PlaneGameObject(PlaneGraphicsObject *gobj)
        : _gfxObj(gobj)
    {
    }
    PlaneGameObject::~PlaneGameObject()
    {
    }

    GraphicsObject *PlaneGameObject::graphicsObject() const
    {
        return _gfxObj;
    }

    const char *PlaneGameObject::name()
    {
        return "PlaneGameObject";
    }
    GraphicsObject *PlaneGameObject::CreateGraphicsObject(GraphicsContext*)
    {
        return _gfxObj;
    }
}
