#pragma once

#include "Material.h"

namespace GlEngine::ShaderFactory
{
    class ShaderFactory;
    class Attribute;
    class ShaderProp;
    class Snippet;
}

class MultiPhongMaterial : public GlEngine::Material
{
public:
    MultiPhongMaterial(Vector<3> color, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
    MultiPhongMaterial(GlEngine::Texture *texture, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
    ~MultiPhongMaterial();

    virtual bool IsOpaque() override;

    virtual GlEngine::TesselationType GetTesselationType() override;

    void Push(GlEngine::ShaderFactory::ShaderFactory &factory) override;

    virtual std::vector<GlEngine::ShaderFactory::ShaderProp*> properties() override;
    virtual std::vector<GlEngine::ShaderFactory::Attribute*> attributes() override;

private:
    GlEngine::Texture *texture;
    Vector<3> color, reflectionCoef;
    float shininess;

    virtual std::string name() override;
    virtual operator bool() override;
};
