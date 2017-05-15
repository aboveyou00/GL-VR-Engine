#pragma once

#include "GameComponent.h"
#include <unordered_map>
#include "NodeSelectionGraphicsObject.h"

class PathingNodeObject;
class PathingNodesGraphicsObject;
class AStarFollower;
namespace GlEngine
{
    class CameraComponent;
}
namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}

typedef std::unordered_map<unsigned, PathingNodeObject*> PathingNodeMap;

class PathingNodesController: public GlEngine::GameComponent
{
public:
    PathingNodesController(std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers, bool editing = false, GlEngine::CameraComponent *camera = nullptr, bool addFollower = true);
    ~PathingNodesController();

    virtual bool InitializeAsync() override;
    virtual void ShutdownAsync() override;

    virtual void Tick(float delta) override;

    virtual void HandleEvent(GlEngine::Events::Event &evt) override;

    bool ExecuteFile(std::string path);
    bool ExecuteStream(std::istream &stream);

    void SaveFile(std::string path);
    void SaveStream(std::ostream &stream);

    bool ExecuteCommand(std::string &command, std::string &line, std::istringstream &stream);

    virtual void GameObjectChanged() override;

    const PathingNodeMap &nodes() const;
    const float radius() const;

private:
    std::map<unsigned, bool> keysDown;
    bool editing, isUpdateQueued;

    std::vector<GlEngine::ShaderFactory::IPropertyProvider*> _providers;
    PathingNodeMap _objects;
    GlEngine::CameraComponent *_camera;

    float _radius;
    PathingNodeObject *_selected;
    PathingNodeObject *createObject(Vector<3> pos);
    PathingNodeObject *createObject(unsigned idx, Vector<3> pos);
    void connectObjects(unsigned idx1, unsigned idx2);
    void disconnectObjects(unsigned idx1, unsigned idx2);
    void autoconnectObject(unsigned idx1, bool update = false);
    void deleteObject(PathingNodeObject *obj);

    void queueUpdate();

    NodeSelectionGraphicsObject *_currentSelection, *_hoverSelection;
    PathingNodesGraphicsObject *_currentGfx;

    bool _addFollower;
    AStarFollower *follower;
};