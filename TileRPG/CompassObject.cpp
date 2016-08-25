#include "stdafx.h"
#include "CompassObject.h"
#include "CompassGraphicsObject.h"

namespace TileRPG
{
    CompassObject::CompassObject()
        : rotation(0)
    {
        RequireTick();
    }
    CompassObject::~CompassObject()
    {
    }

    void CompassObject::Tick(float delta)
    {
        rotation += delta;
    }

    const char *CompassObject::name()
    {
        return "CompassObject";
    }
    GlEngine::GraphicsObject *CompassObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
    {
        return new CompassGraphicsObject();
    }
    void CompassObject::UpdateGraphicsObject(GlEngine::GraphicsContext&, GlEngine::GraphicsObject *object)
    {
        auto gobj = dynamic_cast<CompassGraphicsObject*>(object);
        if (gobj == nullptr) return;

        gobj->SetRotation(rotation);
    }
}
