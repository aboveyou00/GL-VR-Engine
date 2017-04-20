#pragma once
#include "Material.h"

class ClipPlaneMaterial : public GlEngine::Material
{
public:
    ClipPlaneMaterial(std::string name, Vector<4> color);
    ClipPlaneMaterial(std::string name, GlEngine::Texture *tex);
    ~ClipPlaneMaterial();

    virtual void Push(GlEngine::ShaderFactory::ShaderFactory &factory) override;

    virtual std::vector<GlEngine::ShaderFactory::Attribute*> attributes() override;
    virtual std::vector<GlEngine::ShaderFactory::ShaderProp*> properties() override;

    virtual bool IsOpaque() override;
    virtual GlEngine::TesselationType GetTesselationType() override;

    virtual bool isReady() override;

private:
    GlEngine::Texture *tex;
    Vector<4> color;
};
