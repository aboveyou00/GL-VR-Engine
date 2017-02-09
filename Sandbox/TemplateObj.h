#pragma once

#include "GameObject.h"
#include <functional>
#include "Material.h"
#include "IPropertyProvider.h"

class TemplateObj;

typedef GlEngine::Material Material;
typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;

typedef std::function<GlEngine::GraphicsObject*(TemplateObj*, GlEngine::GraphicsContext*)> TplGfxObjectCtorFn;
typedef std::function<void(TemplateObj*, float)> TplTickFn;

namespace GlEngine
{
    class PointLightSource;
}

class TemplateObj : public GlEngine::GameObject
{
public:
    TemplateObj(std::string filename, Material *mat, TplTickFn tick = [](TemplateObj*, float) {});
    TemplateObj(TplGfxObjectCtorFn createGraphicsObject, Material *mat = nullptr, TplTickFn tick = [](TemplateObj*, float){});
    TemplateObj(std::string filename, Material *mat, std::vector<IPropertyProvider*> providers);
    TemplateObj(TplGfxObjectCtorFn createGraphicsObject, Material *mat, std::vector<IPropertyProvider*> providers);
    TemplateObj(std::string filename, Material *mat, std::vector<IPropertyProvider*> providers, TplTickFn tick);
    TemplateObj(TplGfxObjectCtorFn createGraphicsObject, Material *mat, std::vector<IPropertyProvider*> providers, TplTickFn tick);
    ~TemplateObj();

    virtual void Tick(float delta) override;

    virtual std::string name() override;

    virtual GlEngine::GraphicsObject *CreateGraphicsObject(GlEngine::GraphicsContext *ctx) override;

    Material &material() const;
    const std::vector<IPropertyProvider*> &providers() const;
    
private:
    TplGfxObjectCtorFn createGraphicsObject;
    TplTickFn tick;
    Material *_templateMat;
    std::vector<IPropertyProvider*> _providers;

    std::string filename;
    GlEngine::GraphicsObject *createFromFile(GlEngine::GraphicsContext *ctx);
    static GlEngine::GraphicsObject *createFromFileStatic(TemplateObj *self, GlEngine::GraphicsContext *ctx);
};
