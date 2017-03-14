#pragma once

#include "GameComponent.h"

namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}

class FenceComponent : public GlEngine::GameComponent
{
private:
    FenceComponent();
    ~FenceComponent();

public:
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers);
};
