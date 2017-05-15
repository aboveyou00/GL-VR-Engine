#pragma once

#include "GameComponent.h"

class PathingNodeObject;
class PathingNodesController;

namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}

class AStarFollower : public GlEngine::GameComponent
{
public:
    AStarFollower(PathingNodesController *controller, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers, float movementSpeed = .5f);
    ~AStarFollower();

    virtual void Tick(float delta) override;
    void PathfindTo(PathingNodeObject *pno, PathingNodeObject *from = nullptr);

    virtual void GameObjectChanged() override;

private:
    PathingNodesController *controller;
    std::vector<PathingNodeObject*> *path;
    PathingNodeObject* target;
    float speed;

    bool graphicsInitialized;
    std::vector<GlEngine::ShaderFactory::IPropertyProvider*> _providers;
};
