#include "stdafx.h"
#include "CompassObject.h"
#include "CompassGraphicsObject.h"

namespace TileRPG
{
    CompassObject::CompassObject(Vector<3> position, Matrix<4, 4> orientation)
        : GameObject(position, orientation), rotation(0)
    {
        RequireTick(true);
    }
    CompassObject::~CompassObject()
    {
    }

    void CompassObject::Tick(float delta)
    {
        rotation += delta;
    }

    std::string CompassObject::name()
    {
        return "CompassObject";
    }
    GlEngine::GraphicsObject *CompassObject::CreateGraphicsObject(GlEngine::GraphicsContext*)
    {
        return new CompassGraphicsObject();
    }
    void CompassObject::UpdateGraphicsObject(GlEngine::GraphicsContext*, GlEngine::GraphicsObject *object)
    {
        auto gobj = dynamic_cast<CompassGraphicsObject*>(object);
        if (gobj == nullptr) return;

        gobj->SetRotation(rotation);
    }
}
