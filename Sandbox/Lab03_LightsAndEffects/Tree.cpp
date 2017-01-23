#include "stdafx.h"
#include "Tree.h"
#include "ObjGraphicsObject.h"
#include "PhongFogMaterial.h"

Tree::Tree(Vector<3> position, std::vector<IPropertyProvider*> providers)
    : GlEngine::GameObject(position), providers(providers)
{
}
Tree::~Tree()
{
}

const char *Tree::name()
{
    return "Tree";
}

GlEngine::GraphicsObject *Tree::CreateGraphicsObject(GlEngine::GraphicsContext&)
{
    auto mat = new PhongFogMaterial(Vector<3> { 0.f, .6f, 0.f }, { .4f, .4f, .4f }, 8);
    return GlEngine::ObjGraphicsObject::Create("Resources/tree.obj", mat, providers);
}
