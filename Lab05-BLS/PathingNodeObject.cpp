#include "stdafx.h"
#include "PathingNodeObject.h"
#include "ObjLoader.h"
#include "GameObject.h"

PathingNodeObject::PathingNodeObject(unsigned idx, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers)
    : GlEngine::GameComponent("PathingNodeObject"), _idx(idx)
{
    this->_objLoader = new GlEngine::ObjLoader("Resources/sphere_r1.obj"s, providers, GlEngine::ObjLoaderFlag::Graphics);
}
PathingNodeObject::~PathingNodeObject()
{
}

bool PathingNodeObject::InitializeAsync()
{
    if (!GlEngine::GameComponent::InitializeAsync()) return false;

    return true;
}

unsigned PathingNodeObject::idx() const
{
    return _idx;
}
ConnectionList &PathingNodeObject::connections()
{
    return _connections;
}
const ConnectionList &PathingNodeObject::connections() const
{
    return _connections;
}
GlEngine::ObjLoader &PathingNodeObject::objLoader()
{
    return *_objLoader;
}

void PathingNodeObject::GameObjectChanged()
{
    if (this->_objLoader->gameObject() != nullptr) this->_objLoader->gameObject()->RemoveComponent(this->_objLoader);
    if (gameObject() != nullptr) gameObject()->AddComponent(this->_objLoader);
}
