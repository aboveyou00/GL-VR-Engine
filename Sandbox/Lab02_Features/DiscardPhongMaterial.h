#pragma once

#include "PhongMaterial.h"

class DiscardPhongMaterial : GlEngine::PhongMaterial
{
public:
    DiscardPhongMaterial();
    ~DiscardPhongMaterial();

    virtual std::vector<GlEngine::ShaderFactory::Attribute*> attributes() override;

    virtual const char *name() override;
};
