#pragma once

#include "VboGraphicsObject.h"

class StageGraphicsObject : public GlEngine::VboGraphicsObject
{
public:
    StageGraphicsObject(std::string name, bool defaultMaterial = true);
    ~StageGraphicsObject();

    virtual bool InitializeAsync() override;

private:
    bool defaultMaterial;
};
