#pragma once

#include "PhongMaterial.h"

typedef GlEngine::Texture Texture;

class DiscardPhongMaterial : public GlEngine::PhongMaterial
{
public:
    DiscardPhongMaterial(Vector<3> color, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
    DiscardPhongMaterial(Texture *texture, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
    ~DiscardPhongMaterial();

    virtual std::vector<GlEngine::ShaderFactory::Attribute*> attributes() override;
};
