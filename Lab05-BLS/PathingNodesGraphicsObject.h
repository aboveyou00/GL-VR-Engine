#pragma once

#include "LineSegmentGraphicsObject.h"
#include "PathingNodesController.h"

class PathingNodesGraphicsObject : public GlEngine::LineSegmentGraphicsObject
{
public:
    PathingNodesGraphicsObject(const PathingNodeMap &nodes, float radius);
    ~PathingNodesGraphicsObject();

    virtual bool InitializeAsync() override;

private:
    const PathingNodeMap &_nodes;
    float _radius;
};
