#pragma once

#include "Material.h"

class PhongFlatMaterial : public GlEngine::Material
{
public:
    PhongFlatMaterial(Vector<3> color, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
    PhongFlatMaterial(GlEngine::Texture *texture, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
    ~PhongFlatMaterial();

public:
    void Push(GlEngine::ShaderFactory::ShaderFactory &factory) override;

    bool IsOpaque() override;
    GlEngine::TesselationType GetTesselationType() override;

    virtual std::vector<GlEngine::ShaderFactory::ShaderProp*> properties() override;
    virtual std::vector<GlEngine::ShaderFactory::Attribute*> attributes() override;

    const char *name() override;
    operator bool() override;

private:
    GlEngine::Texture *texture;
    Vector<3> color, reflectionCoef;
    float shininess;
};
