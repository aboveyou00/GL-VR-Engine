#pragma once

#include "Image2dGraphicsObject.h"

class XpBarGameObject;

class XpBarGraphicsObject : public GlEngine::Image2dGraphicsObject
{
public:
    XpBarGraphicsObject(XpBarGameObject *obj);
    ~XpBarGraphicsObject();

private:
    XpBarGameObject *xpObj;
};
