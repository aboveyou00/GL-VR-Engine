#pragma once

#include "PlaneGraphicsObject.h"
#include "ClipPlaneMaterial.h"

class ClipPlaneGraphicsObject: public GlEngine::PlaneGraphicsObject
{
public:
    ClipPlaneGraphicsObject(std::string name, GlEngine::Texture *tex);
    ClipPlaneGraphicsObject(std::string name, Vector<4> color);
    ~ClipPlaneGraphicsObject();
};
