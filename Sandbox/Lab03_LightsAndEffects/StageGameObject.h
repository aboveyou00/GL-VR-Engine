#pragma once

#include "GameObject.h"
#include "IPropertyProvider.h"
typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;

class StageGameObject : public GlEngine::GameObject
{
public:
    StageGameObject(std::vector<IPropertyProvider*> providers = { });
    ~StageGameObject();

    virtual const char *name() override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext &ctx) override;

private:
    std::vector<IPropertyProvider*> providers;
};
