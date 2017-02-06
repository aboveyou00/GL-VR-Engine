#pragma once

#include "GameObject.h"

class XpBarGameObject: public GlEngine::GameObject
{
public:
    XpBarGameObject();
    ~XpBarGameObject();

    float xpLast();
    float xpTotal();
    float xpNext();

    float xpPercentage();

    virtual const char *name() override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;

private:
    float lastLevelXp, nextLevelXp, currentXpTotal;
};
