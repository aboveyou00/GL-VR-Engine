#pragma once

#include "LineSegmentGraphicsObject.h"

class GridGraphicsObject : public GlEngine::LineSegmentGraphicsObject
{
public:
    GridGraphicsObject(Vector<4> color, Vector<3> origin = { 0, 0, 0 }, Vector<2> cellSizes = { 1, 1 }, Vector<2, int> cellCount = { 10, 10 }, bool showOrigin = true);
    ~GridGraphicsObject();

    virtual bool InitializeAsync() override;

private:
    Vector<4> _color;
    Vector<3> _origin;
    Vector<2> _cellSizes;
    Vector<2, int> _cellCount;
    bool _showOrigin;
};
