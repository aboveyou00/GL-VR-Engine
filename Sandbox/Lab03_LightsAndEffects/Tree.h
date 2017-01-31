#pragma once

#include "GameObject.h"

namespace GlEngine::ShaderFactory
{
    class IPropertyProvider;
}
typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;

class Tree : public GlEngine::GameObject
{
public:
    Tree(Vector<3> position, std::vector<IPropertyProvider*> providers);
    ~Tree();

    virtual const char *name() override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;

private:
    std::vector<IPropertyProvider*> providers;
};
