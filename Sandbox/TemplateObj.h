#pragma once

#include "GameObject.h"
#include <functional>
#include "TemplateMaterial.h"
#include "Material.h"
#include "IPropertyProvider.h"
#include <functional>

typedef GlEngine::Material Material;
typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;

namespace GlEngine
{
    class PointLightSource;
}

class TemplateObj : public GlEngine::GameObject
{
public:
    TemplateTorus(Material* mat, std::vector<IPropertyProvider*> providers, std::function<void(TemplateTorus*, float)> tick);
    ~TemplateTorus();

    virtual void Tick(float delta) override;

    virtual const char *name() override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;
    
    std::function<GlEngine::GraphicsObject*(TemplateObj*, GlEngine::GraphicsContext& ctx)> createGraphicsObject;
    Material* templateMat;
    std::vector<IPropertyProvider*> providers;
    std::function<void(TemplateObj*, float)> tick;
};
