#pragma once

#include "Material.h"
#include <functional>

typedef GlEngine::ShaderFactory::ShaderFactory ShaderFactory;
typedef GlEngine::ShaderFactory::ShaderProp ShaderProp;
typedef GlEngine::ShaderFactory::Attribute Attribute;
typedef GlEngine::TesselationType TesselationType;

class TemplateMaterial : public GlEngine::Material
{
public:
    TemplateMaterial(std::vector<ShaderProp*> props, std::vector<Attribute*> attributes, std::function<void(ShaderFactory&)> push);
    ~TemplateMaterial();

public:
    void Push(GlEngine::ShaderFactory::ShaderFactory &factory) override;

    bool IsOpaque() override;
    TesselationType GetTesselationType() override;

    virtual std::vector<ShaderProp*> properties() override;
    virtual std::vector<Attribute*> attributes() override;

    const char *name() override;
    operator bool() override;

private:
    std::vector<ShaderProp*> props;
    std::vector<Attribute*> attribs;
    std::function<void(ShaderFactory&)> push;
};
