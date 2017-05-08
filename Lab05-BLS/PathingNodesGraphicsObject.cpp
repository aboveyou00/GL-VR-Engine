#include "stdafx.h"
#include "PathingNodesGraphicsObject.h"
#include "PathingNodeObject.h"
#include "GameObject.h"

PathingNodesGraphicsObject::PathingNodesGraphicsObject(const PathingNodeMap &nodes)
    : GlEngine::LineSegmentGraphicsObject("PathingNodesGraphicsObject", [](GlEngine::Material*) { return nullptr; }), _nodes(nodes)
{
}
PathingNodesGraphicsObject::~PathingNodesGraphicsObject()
{
}

bool PathingNodesGraphicsObject::InitializeAsync()
{
    if (!GlEngine::LineSegmentGraphicsObject::InitializeAsync()) return false;

    auto renderOffset = Vector<3>{ 0, 0.2f, 0 };
    float radius = 1.f;

    for (auto itFirst = _nodes.begin(); itFirst != _nodes.end(); itFirst++)
    {
        auto pno = itFirst->second;
        for (auto itSecond = pno->connections().begin(); itSecond != pno->connections().end(); itSecond++)
        {
            auto checkPno = *itSecond;

            auto center = pno->gameObject()->globalTransform()->position() + renderOffset;
            auto otherCenter = checkPno->gameObject()->globalTransform()->position() + renderOffset;
            auto forwardUnnormalized = otherCenter - center;
            auto forward = forwardUnnormalized.Normalized();
            auto up = Vector<3>{ 0, 1, 0 };
            auto side = forward.Cross(up);

            unsigned idx0, idx1;

            idx0 = AddVertex(center + (side * radius), Vector<4> { 1, 0, 0, 1 });
            idx1 = AddVertex(otherCenter + (side * radius), Vector<4> { 1, 1, 0, 1 });
            AddLine(idx0, idx1);
        }
    }

    return true;
}
