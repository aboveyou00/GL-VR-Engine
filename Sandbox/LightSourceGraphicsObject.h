#pragma once

#include "VboGraphicsObject.h"

class LightSourceGraphicsObject : public GlEngine::VboGraphicsObject
{
public:
    LightSourceGraphicsObject();
    ~LightSourceGraphicsObject();

    bool Initialize() override;

    virtual const char *name() override;
};
