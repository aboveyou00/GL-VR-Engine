#pragma once

#include "GameObject.h"
#include "GraphicsObject.h"
#include <functional>
#include "Material.h"
#include "IPropertyProvider.h"

class TemplateObj;

typedef GlEngine::Material Material;
typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;

typedef std::function<void(TemplateObj*, float)> TplTickFn;

namespace GlEngine
{
    class PointLightSource;
}

class TemplateObj : public GlEngine::GameComponent
{
public:
    TemplateObj(std::string filename, Material *mat, TplTickFn tick = [](TemplateObj*, float) {});
    TemplateObj(GlEngine::GraphicsObject *gfxObj, Material *mat = nullptr, TplTickFn tick = [](TemplateObj*, float){});
    TemplateObj(std::string filename, Material *mat, std::vector<IPropertyProvider*> providers);
    TemplateObj(GlEngine::GraphicsObject *gfxObj, Material *mat, std::vector<IPropertyProvider*> providers);
    TemplateObj(std::string filename, Material *mat, std::vector<IPropertyProvider*> providers, TplTickFn tick);
    TemplateObj(GlEngine::GraphicsObject *gfxObj, Material *mat, std::vector<IPropertyProvider*> providers, TplTickFn tick);
    ~TemplateObj();

    virtual void Tick(float delta) override;

    Material &material() const;
    const std::vector<IPropertyProvider*> &providers() const;

private:
    TplTickFn tick;
    GlEngine::GraphicsObject *gfxObj;
    Material *_templateMat;
    std::vector<IPropertyProvider*> _providers;

    GlEngine::GraphicsObject *createFromFile(std::string name, std::string filename);
};
