#include "stdafx.h"
#include "TemplateObj.h"
#include "TemplateMaterial.h"
#include "TemplateMaterialFactory.h"
#include "ObjGraphicsObject.h"
#include "DiffuseMaterial.h"
#include "RandomUtils.h"
#include "MatrixStack.h"
#include "AmbientLightSource.h"
#include "PointLightSource.h"
#include "LabControls.h"
#include "LightSourceObject.h"

TemplateObj::TemplateObj(std::string filename, Material *mat, TplTickFn tick)
    : TemplateObj(filename, mat, {}, tick)
{
}
TemplateObj::TemplateObj(TplGfxObjectCtorFn createGraphicsObject, Material *mat, TplTickFn tick)
    : TemplateObj(createGraphicsObject, mat, {}, tick)
{
}
TemplateObj::TemplateObj(std::string filename, Material *mat, std::vector<IPropertyProvider*> providers)
    : TemplateObj(filename, mat, providers, [](TemplateObj*, float) {})
{
}
TemplateObj::TemplateObj(TplGfxObjectCtorFn createGraphicsObject, Material *mat, std::vector<IPropertyProvider*> providers)
    : TemplateObj(createGraphicsObject, mat, providers, [](TemplateObj*, float) {})
{
}
TemplateObj::TemplateObj(std::string filename, Material *mat, std::vector<IPropertyProvider*> providers, TplTickFn tick)
    : filename(filename), createGraphicsObject(createFromFileStatic), _templateMat(mat), _providers(providers), tick(tick)
{
    if (mat == nullptr) _templateMat = TemplateMaterial::Factory()->Create();
    RequireTick(true);
}
TemplateObj::TemplateObj(TplGfxObjectCtorFn createGraphicsObject, Material *mat, std::vector<IPropertyProvider*> providers, TplTickFn tick)
    : createGraphicsObject(createGraphicsObject), _templateMat(mat), _providers(providers), tick(tick)
{
    if (mat == nullptr) _templateMat = TemplateMaterial::Factory()->Create();
    RequireTick(true);
}
TemplateObj::~TemplateObj()
{
}

void TemplateObj::Tick(float delta)
{
    tick(this, delta);
}

std::string TemplateObj::name()
{
    return "TemplateObj";
}

GlEngine::GraphicsObject *TemplateObj::CreateGraphicsObject(GlEngine::GraphicsContext *ctx)
{
    return createGraphicsObject(this, ctx);
}

Material &TemplateObj::material() const
{
    return *_templateMat;
}
const std::vector<IPropertyProvider*> &TemplateObj::providers() const
{
    return _providers;
}

GlEngine::GraphicsObject *TemplateObj::createFromFile(GlEngine::GraphicsContext*)
{
    return GlEngine::ObjGraphicsObject::Create(filename.c_str(), _templateMat, _providers);
}
GlEngine::GraphicsObject *TemplateObj::createFromFileStatic(TemplateObj *self, GlEngine::GraphicsContext *ctx)
{
    assert(self != nullptr);
    return self->createFromFile(ctx);
}
