#include "stdafx.h"
#include "AStarFollower.h"
#include "PathingNodesController.h"
#include "PathingNodeObject.h"
#include "GameObject.h"
#include "RandomUtils.h"
#include "ObjLoader.h"
#include "AStarPathfinding.h"

AStarFollower::AStarFollower(PathingNodesController *controller, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers, float movementSpeed)
    : GlEngine::GameComponent("AStarFollower"s), controller(controller), target(nullptr), path(nullptr), speed(movementSpeed), _providers(providers), graphicsInitialized(false)
{
}
AStarFollower::~AStarFollower()
{
}

void AStarFollower::Tick(float delta)
{
    if (target == nullptr)
    {
        float currentDistSquared = std::numeric_limits<float>::infinity();
        PathingNodeObject *currentNode = nullptr;
        for (auto &kvp : controller->nodes())
        {
            auto &node = *kvp.second;
            auto ray = gameObject()->globalTransform()->position() - node.gameObject()->globalTransform()->position();
            auto distSquared = ray.LengthSquared();
            if (distSquared > currentDistSquared) continue;
            //TODO: check if the node is visible
            currentNode = &node;
            currentDistSquared = distSquared;
        }
        if (currentNode != nullptr)
        {
            target = currentNode;
            SafeDelete(path);
            path = new std::vector<PathingNodeObject*> { target };
        }
    }
    if (target == nullptr) return;

    auto &nodes = controller->nodes();
    if ((path == nullptr || path->size() == 0) && nodes.size() > 0)
    {
        auto idx = GlEngine::Util::random(nodes.size());
        auto newTargetIt = nodes.begin();
        std::advance(newTargetIt, idx);
        auto newTarget = newTargetIt->second;
        auto fromNode = target;
        path = pathfind_astar(fromNode, newTarget);
        if (path != nullptr) target = newTarget;
    }
    if (path == nullptr || path->size() == 0) return;

    auto &nextNode = **(path->end() - 1);
    float moveDistance = delta * speed;
    auto ray = nextNode.gameObject()->globalTransform()->position() - gameObject()->globalTransform()->position();
    float maxMoveDistance = ray.Length();
    if (moveDistance >= maxMoveDistance)
    {
        moveDistance = maxMoveDistance;
        path->erase(path->end() - 1);
    }
    else gameObject()->globalTransform()->Translate(ray.Normalized(moveDistance));
}
void AStarFollower::PathfindTo(PathingNodeObject *pno, PathingNodeObject *from)
{
    if (from == nullptr)
    {
        if (path->size() == 0) return;
        from = *(path->end() - 1);
    }

    path = pathfind_astar(from, pno);
    if (path != nullptr) target = pno;
}

void AStarFollower::GameObjectChanged()
{
    auto gobj = gameObject();
    if (gobj == nullptr) return;
    assert(!graphicsInitialized);
    graphicsInitialized = true;
    gobj->AddComponent(new GlEngine::ObjLoader("Resources/astar_follower.obj"s, _providers, GlEngine::ObjLoaderFlag::Graphics));
}
