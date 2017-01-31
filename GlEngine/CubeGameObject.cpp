#include "stdafx.h"
#include "CubeGameObject.h"

namespace GlEngine
{
    CubeGameObject::CubeGameObject(CubeGraphicsObject *gobj)
        : _gfxObj(gobj)
    {
        RequireTick(true);
    }
    CubeGameObject::~CubeGameObject()
    {
    }

    Vector<3> CubeGameObject::rotationSpeed()
    {
        return _rotationSpeed;
    }
    void CubeGameObject::SetRotationSpeed(Vector<3> rot)
    {
        _rotationSpeed = rot;
    }

    GraphicsObject *CubeGameObject::graphicsObject() const
    {
        return _gfxObj;
    }

    void CubeGameObject::Tick(float delta)
    {
        RotateX(delta * _rotationSpeed[0]);
        RotateY(delta * _rotationSpeed[1]);
        RotateZ(delta * _rotationSpeed[2]);
    }

    const char *CubeGameObject::name()
    {
        return "CubeGameObject";
    }
    GraphicsObject * CubeGameObject::CreateGraphicsObject(GraphicsContext*)
    {
        return _gfxObj;
    }
}
