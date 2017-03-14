#pragma once

#include "AudioSourceComponent.h"

namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}

class PageComponent : public GlEngine::AudioSourceComponent
{
private:
    PageComponent(int pageNumber);
    ~PageComponent();

public:
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, int pageNumber, Vector<3> position, float angle, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers);

    bool FindPage();

private:
    bool isFound;
    int pageNumber;
    GameComponent *wallGfx;
    GameComponent *pageGfx;
};
