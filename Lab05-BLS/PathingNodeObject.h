#pragma once

#include "GameComponent.h"

class PathingNodeObject;

namespace GlEngine {
    class ObjLoader;
}
namespace GlEngine::ShaderFactory {
    class IPropertyProvider;
}

typedef std::vector<PathingNodeObject*> ConnectionList;

class PathingNodeObject : public GlEngine::GameComponent
{
public:
    PathingNodeObject(unsigned idx, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers);
    ~PathingNodeObject();

    virtual bool InitializeAsync() override;

    unsigned idx() const;
    ConnectionList &connections();
    const ConnectionList &connections() const;
    GlEngine::ObjLoader &objLoader();

    virtual void GameObjectChanged() override;

private:
    unsigned _idx;
    ConnectionList _connections;
    GlEngine::ObjLoader *_objLoader;
};
