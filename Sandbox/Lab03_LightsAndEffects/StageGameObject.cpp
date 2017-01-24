#include "stdafx.h"
#include "StageGameObject.h"
#include "StageGraphicsObject.h"

StageGameObject::StageGameObject(std::vector<IPropertyProvider*> providers)
    : providers(providers)
{
}
StageGameObject::~StageGameObject()
{
}

const char *StageGameObject::name()
{
    return "StageGameObject";
}
GlEngine::GraphicsObject *StageGameObject::CreateGraphicsObject(GlEngine::GraphicsContext&)
{
    auto gobj = new StageGraphicsObject();
    for (auto it = providers.begin(); it != providers.end(); it++)
        gobj->AddPropertyProvider(*it);
    return gobj;
}
