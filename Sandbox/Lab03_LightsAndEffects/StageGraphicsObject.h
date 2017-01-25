#pragma once

#include "VboGraphicsObject.h"

class StageGraphicsObject : public GlEngine::VboGraphicsObject
{
public:
    StageGraphicsObject();
    StageGraphicsObject(bool defaultMaterial);
    ~StageGraphicsObject();

    virtual bool Initialize() override;

private:
    bool defaultMaterial;
};
