#include "stdafx.h"
#include "ClipPlaneGraphicsObject.h"

ClipPlaneGraphicsObject::ClipPlaneGraphicsObject(std::string name, GlEngine::Texture *tex)
    : PlaneGraphicsObject(name, new ClipPlaneMaterial("ClipPlaneMat"s, tex), { 2, 2 }, { 1, 1 }, { 1, 1 }, GlEngine::PlaneDirection::Zp)
{
}
ClipPlaneGraphicsObject::ClipPlaneGraphicsObject(std::string name, Vector<4> color)
    : PlaneGraphicsObject(name, new ClipPlaneMaterial("ClipPlaneMat"s, color), { 2, 2 }, { 1, 1 }, { 1, 1 }, GlEngine::PlaneDirection::Zp)
{
}
ClipPlaneGraphicsObject::~ClipPlaneGraphicsObject()
{
}
