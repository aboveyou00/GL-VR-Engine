#include "stdafx.h"
#include "CrosshairGraphicsObject.h"

CrosshairGraphicsObject::CrosshairGraphicsObject(float dist)
    : CrosshairGraphicsObject(dist, Vector<4> { 1.f, 0, 0, 1 })
{
}
CrosshairGraphicsObject::CrosshairGraphicsObject(float dist, Vector<3> color)
    : CrosshairGraphicsObject(dist, Vector<4> { color[0], color[1], color[2], 1 })
{
}
CrosshairGraphicsObject::CrosshairGraphicsObject(float dist, Vector<4> color)
    : LineSegmentGraphicsObject("CrosshairGraphicsObject", [](GlEngine::Material*) { return nullptr; }, false), _dist(dist), _color(color)
{
}
CrosshairGraphicsObject::~CrosshairGraphicsObject()
{
}

bool CrosshairGraphicsObject::InitializeAsync()
{
    if (!GlEngine::LineSegmentGraphicsObject::InitializeAsync()) return false;

    int idx0, idx1;

    idx0 = AddVertex({ -_dist, 0, 0 }, _color);
    idx1 = AddVertex({  _dist, 0, 0 }, _color);
    AddLine({ idx0, idx1 });

    idx0 = AddVertex({ 0, -_dist, 0 }, _color);
    idx1 = AddVertex({ 0,  _dist, 0 }, _color);
    AddLine({ idx0, idx1 });

    idx0 = AddVertex({ 0, 0, -_dist }, _color);
    idx1 = AddVertex({ 0, 0,  _dist }, _color);
    AddLine({ idx0, idx1 });

    return true;
}
