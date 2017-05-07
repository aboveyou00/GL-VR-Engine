#pragma once

#include "LineSegmentGraphicsObject.h"

class NodeSelectionGraphicsObject : public GlEngine::LineSegmentGraphicsObject
{
public:
    NodeSelectionGraphicsObject(Vector<4> color);
    ~NodeSelectionGraphicsObject();

    virtual bool InitializeAsync() override;

private:
    Vector<4> _color;
};
