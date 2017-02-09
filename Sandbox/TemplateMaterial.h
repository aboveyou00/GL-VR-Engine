#pragma once

#include "Material.h"
#include <functional>

typedef GlEngine::ShaderFactory::ShaderFactory ShaderFactory;
typedef GlEngine::ShaderFactory::ShaderProp ShaderProp;
typedef GlEngine::ShaderFactory::Attribute Attribute;
typedef GlEngine::TesselationType TesselationType;

class TemplateMaterialFactory;

class TemplateMaterial : public GlEngine::Material
{
private:
    TemplateMaterial(TemplateMaterialFactory *factory);
    ~TemplateMaterial();

public:
    friend class TemplateMaterialFactory;
    static TemplateMaterialFactory *Factory();

    void Push(GlEngine::ShaderFactory::ShaderFactory &factory) override;

    bool IsOpaque() override;
    TesselationType GetTesselationType() override;

    virtual std::vector<ShaderProp*> properties() override;
    virtual std::vector<Attribute*> attributes() override;

    virtual std::string name() override;
    virtual operator bool() override;

private:
    TemplateMaterialFactory *_factory;
};
