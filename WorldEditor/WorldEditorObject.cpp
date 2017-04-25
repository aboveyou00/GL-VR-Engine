#include "stdafx.h"
#include "WorldEditorObject.h"
#include "ObjLoader.h"
#include "PhongMaterial.h"
#include "GameObject.h"

WorldEditorObject::WorldEditorObject(std::string objPath, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers)
    : GlEngine::GameComponent("WorldEditorObject"s)
{
    this->_objLoader = new GlEngine::ObjLoader(objPath, providers, GlEngine::ObjLoaderFlag::Graphics);
    this->_mat = new GlEngine::PhongMaterial({ 1, 0, 0 }, { .5, .5, .5 }, 10);
    this->_objLoader->OverrideMaterial(this->_mat);
}
WorldEditorObject::~WorldEditorObject()
{
}

bool WorldEditorObject::InitializeAsync()
{
    if (!GlEngine::GameComponent::InitializeAsync()) return false;

    return true;
}

GlEngine::ObjLoader &WorldEditorObject::objLoader()
{
    return *_objLoader;
}
GlEngine::PhongMaterial &WorldEditorObject::mat()
{
    return *_mat;
}

void WorldEditorObject::GameObjectChanged()
{
    if (this->_objLoader->gameObject() != nullptr) this->_objLoader->gameObject()->RemoveComponent(this->_objLoader);
    if (gameObject() != nullptr)
    {
        gameObject()->AddComponent(this->_objLoader);
    }
}
