#pragma once

#include "GameComponent.h"

namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}

class SlenderComponent : public GlEngine::GameComponent
{
private:
    SlenderComponent(GlEngine::GameObject *player);
    ~SlenderComponent();

public:
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, GlEngine::GameObject *player, Vector<3> position, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers);

    virtual void Tick(float delta) override;

private:
    GlEngine::GameObject *player;
};
