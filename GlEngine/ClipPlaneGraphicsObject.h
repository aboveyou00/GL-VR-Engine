#pragma once

#include "PlaneGraphicsObject.h"
#include "ClipPlaneMaterial.h"

namespace GlEngine
{
    class ENGINE_SHARED ClipPlaneGraphicsObject : public PlaneGraphicsObject
    {
    public:
        ClipPlaneGraphicsObject(std::string name, Texture *tex);
        ClipPlaneGraphicsObject(std::string name, Vector<4> color);
        ~ClipPlaneGraphicsObject();
    };
}
