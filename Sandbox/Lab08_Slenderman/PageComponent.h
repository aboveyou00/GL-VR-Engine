#pragma once

#include "GameComponent.h"

namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}

class PageComponent : public GlEngine::GameComponent
{
private:
    PageComponent(int pageNumber);
    ~PageComponent();

public:
    static GlEngine::GameObject *Create(GlEngine::Frame *frame, int pageNumber, Vector<3> position, float angle, std::vector<GlEngine::ShaderFactory::IPropertyProvider*> providers);

    void FindPage();

private:
    bool isFound;
    int pageNumber;
    GameComponent *wallGfx;
    GameComponent *pageGfx;
};
