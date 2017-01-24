#pragma once

#include "Material.h"

namespace GlEngine::ShaderFactory
{
    class ShaderFactory;
    class Attribute;
    class ShaderProp;
    class Snippet;
}
typedef GlEngine::ShaderFactory::ShaderFactory ShaderFactory;
typedef GlEngine::ShaderFactory::Attribute Attribute;
typedef GlEngine::ShaderFactory::ShaderProp ShaderProp;
typedef GlEngine::ShaderFactory::Snippet Snippet;

class MultiPhongMaterial : public GlEngine::Material
{
public:
    MultiPhongMaterial(Vector<3> color, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
    MultiPhongMaterial(GlEngine::Texture *texture, Vector<3> reflectionCoef = { 1.f, 1.f, 1.f }, float shininess = 8);
    ~MultiPhongMaterial();

    virtual bool IsOpaque() override;

    virtual GlEngine::TesselationType GetTesselationType() override;

    void Push(ShaderFactory &factory) override;

    virtual std::vector<ShaderProp*> properties() override;
    virtual std::vector<Attribute*> attributes() override;

private:
    GlEngine::Texture *texture;
    Vector<3> color, reflectionCoef;
    float shininess;

    // Inherited via Material
    virtual const char * name() override;
    virtual operator bool() override;
};
