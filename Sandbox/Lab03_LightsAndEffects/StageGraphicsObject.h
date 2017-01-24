#pragma once

#include "VboGraphicsObject.h"

class StageGraphicsObject : public GlEngine::VboGraphicsObject
{
public:
    StageGraphicsObject();
    ~StageGraphicsObject();

    virtual bool Initialize() override;
};
