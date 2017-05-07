#include "stdafx.h"
#include "NodeSelectionGraphicsObject.h"
#include "LineSegmentMaterial.h"

NodeSelectionGraphicsObject::NodeSelectionGraphicsObject(Vector<4> color)
    : GlEngine::LineSegmentGraphicsObject("NodeSelection", [](GlEngine::Material*) { return nullptr; }, false), _color(color)
{
}
NodeSelectionGraphicsObject::~NodeSelectionGraphicsObject()
{
}

bool NodeSelectionGraphicsObject::InitializeAsync()
{
    if (!GlEngine::LineSegmentGraphicsObject::InitializeAsync()) return false;

    auto mmm = AddVertex({ -1, -1, -1 }, _color);
    auto pmm = AddVertex({  1, -1, -1 }, _color);
    auto mpm = AddVertex({ -1,  1, -1 }, _color);
    auto ppm = AddVertex({  1,  1, -1 }, _color);
    auto mmp = AddVertex({ -1, -1,  1 }, _color);
    auto pmp = AddVertex({  1, -1,  1 }, _color);
    auto mpp = AddVertex({ -1,  1,  1 }, _color);
    auto ppp = AddVertex({  1,  1,  1 }, _color);

    AddLine(mmm, pmm);
    AddLine(mmm, mpm);
    AddLine(mmm, mmp);

    AddLine(pmm, ppm);
    AddLine(pmm, pmp);

    AddLine(mpm, ppm);
    AddLine(mpm, mpp);

    AddLine(mmp, pmp);
    AddLine(mmp, mpp);

    AddLine(ppp, ppm);
    AddLine(ppp, pmp);
    AddLine(ppp, mpp);

    return true;
}
