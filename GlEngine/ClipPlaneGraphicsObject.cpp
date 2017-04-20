#include "stdafx.h"
#include "ClipPlaneGraphicsObject.h"

namespace GlEngine
{
    ClipPlaneGraphicsObject::ClipPlaneGraphicsObject(std::string name, Texture *tex)
        : PlaneGraphicsObject(name, new ClipPlaneMaterial("ClipPlaneMat"s, tex), { 2, 2 }, { 1, 1 }, { 1, 1 }, PlaneDirection::Zp)
    {
    }
    ClipPlaneGraphicsObject::ClipPlaneGraphicsObject(std::string name, Vector<4> color)
        : PlaneGraphicsObject(name, new ClipPlaneMaterial("ClipPlaneMat"s, color), { 2, 2 }, { 1, 1 }, { 1, 1 }, PlaneDirection::Zp)
    {
    }
    ClipPlaneGraphicsObject::~ClipPlaneGraphicsObject()
    {
    }
}
