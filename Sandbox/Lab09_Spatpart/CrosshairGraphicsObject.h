#pragma once
#include "LineSegmentGraphicsObject.h"

class CrosshairGraphicsObject: public GlEngine::LineSegmentGraphicsObject
{
public:
    CrosshairGraphicsObject(float dist = 1.f);
    CrosshairGraphicsObject(float dist, Vector<3> color);
    CrosshairGraphicsObject(float dist, Vector<4> color);
    ~CrosshairGraphicsObject();

    virtual bool InitializeAsync() override;

private:
    float _dist;
    Vector<4> _color;
};
