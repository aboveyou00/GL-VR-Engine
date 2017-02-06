#include "stdafx.h"
#include "XpBarGameObject.h"
#include "XpBarGraphicsObject.h"

XpBarGameObject::XpBarGameObject()
    : lastLevelXp(400.f), currentXpTotal(433.f), nextLevelXp(500.f)
{
}
XpBarGameObject::~XpBarGameObject()
{
}

float XpBarGameObject::xpLast()
{
    return lastLevelXp;
}
float XpBarGameObject::xpTotal()
{
    return currentXpTotal;
}
float XpBarGameObject::xpNext()
{
    return nextLevelXp;
}

float XpBarGameObject::xpPercentage()
{
    auto last = xpLast();
    return (xpTotal() - last) / (xpNext() - last);
}

const char *XpBarGameObject::name()
{
    return "XpBarGameObject";
}

GlEngine::GraphicsObject* XpBarGameObject::CreateGraphicsObject(GlEngine::GraphicsContext*)
{
    return new XpBarGraphicsObject(this);
}
