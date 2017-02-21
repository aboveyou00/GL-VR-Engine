#include "stdafx.h"
#include "Tree.h"
#include "GameObject.h"
#include "ObjGraphicsObject.h"
#include "PhongFogMaterial.h"

Tree::Tree()
{
    assert(false);
}
Tree::~Tree()
{
}

GlEngine::GameObject *Tree::Create(GlEngine::Frame *frame, std::string name, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers)
{
    auto gobj = new GlEngine::GameObject(frame, name);
    auto mat = new PhongFogMaterial(Vector<3> { 0.f, .6f, 0.f }, { .4f, .4f, .4f }, 8);
    auto objObj = GlEngine::ObjGraphicsObject::Create(name, "Resources/tree.obj", mat, providers);
    gobj->AddComponent(objObj);
    return gobj;
}
