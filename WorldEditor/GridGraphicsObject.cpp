#include "stdafx.h"
#include "GridGraphicsObject.h"

GridGraphicsObject::GridGraphicsObject(Vector<4> color, Vector<3> origin, Vector<2> cellSizes, Vector<2, int> cellCount, bool showOrigin)
    : GlEngine::LineSegmentGraphicsObject("GridGraphicsObject", [](void*){return nullptr;}), _color(color), _origin(origin), _cellSizes(cellSizes), _cellCount(cellCount), _showOrigin(showOrigin)
{
}
GridGraphicsObject::~GridGraphicsObject()
{
}

bool GridGraphicsObject::InitializeAsync()
{
    if (!GlEngine::LineSegmentGraphicsObject::InitializeAsync()) return false;

    auto zmin = _origin[2] - _cellCount[1] * _cellSizes[1];
    auto zmax = _origin[2] + _cellCount[1] * _cellSizes[1];
    for (int q = -_cellCount[0]; q <= _cellCount[0]; q++)
    {
        auto idx1 = AddVertex({ _origin[0] - q * _cellSizes[0], _origin[1], zmin }, _color);
        auto idx2 = AddVertex({ _origin[0] - q * _cellSizes[0], _origin[1], zmax }, _color);
        AddLine(idx1, idx2);
    }

    auto xmin = _origin[0] - _cellCount[0] * _cellSizes[0];
    auto xmax = _origin[0] + _cellCount[0] * _cellSizes[0];
    for (int w = -_cellCount[1]; w <= _cellCount[1]; w++)
    {
        auto idx1 = AddVertex({ xmin, _origin[1], _origin[2] - w * _cellSizes[1] }, _color);
        auto idx2 = AddVertex({ xmax, _origin[1], _origin[2] - w * _cellSizes[1] }, _color);
        AddLine(idx1, idx2);
    }

    if (_showOrigin)
    {
        Vector<4> originColor = { _color[1], _color[2], _color[0], _color[3] };
        auto idx1 = AddVertex({ _origin[0], _origin[1] - 0, _origin[1] }, originColor);
        auto idx2 = AddVertex({ _origin[0], _origin[1] + _cellSizes[0], _origin[1] }, originColor);
        AddLine(idx1, idx2);
    }

    return true;
}
