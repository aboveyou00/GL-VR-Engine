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
#include "LightSourceObject.h"
#include "VboFactoryGraphicsObjectImpl.h"

TemplateObj::TemplateObj(std::string filename, Material *mat, TplTickFn tick)
    : TemplateObj(filename, mat, {}, tick)
{
}
TemplateObj::TemplateObj(GlEngine::GraphicsObject *gfxObj, Material *mat, TplTickFn tick)
    : TemplateObj(gfxObj, mat, {}, tick)
{
}
TemplateObj::TemplateObj(std::string filename, Material *mat, std::vector<IPropertyProvider*> providers)
    : TemplateObj(filename, mat, providers, [](TemplateObj*, float) {})
{
}
TemplateObj::TemplateObj(GlEngine::GraphicsObject *gfxObj, Material *mat, std::vector<IPropertyProvider*> providers)
    : TemplateObj(gfxObj, mat, providers, [](TemplateObj*, float) {})
{
}
TemplateObj::TemplateObj(std::string filename, Material *mat, std::vector<IPropertyProvider*> providers, TplTickFn tick)
    : TemplateObj(createFromFile("TemplateObjGfx", filename), mat, providers, tick)
{
}
TemplateObj::TemplateObj(GlEngine::GraphicsObject *gfxObj, Material *mat, std::vector<IPropertyProvider*> providers, TplTickFn tick)
    : GameComponent("TemplateObj"), gfxObj(gfxObj), _templateMat(mat), _providers(providers), tick(tick)
{
    if (mat == nullptr) _templateMat = TemplateMaterial::Factory()->Create();

    for (size_t q = 0; q < this->providers().size(); q++)
        gfxObj->AddPropertyProvider(this->providers()[q]);
    auto vboFacGfx = dynamic_cast<GlEngine::Impl::VboFactoryGraphicsObjectImpl*>(&this->material());
    if (vboFacGfx != nullptr)
    {
        vboFacGfx->SetMaterial(&this->material());
    }
}
TemplateObj::~TemplateObj()
{
}

void TemplateObj::Tick(float delta)
{
    tick(this, delta);
}

Material &TemplateObj::material() const
{
    return *_templateMat;
}
const std::vector<IPropertyProvider*> &TemplateObj::providers() const
{
    return _providers;
}

GlEngine::GraphicsObject *TemplateObj::createFromFile(std::string name, std::string filename)
{
    return GlEngine::ObjGraphicsObject::Create(name, filename.c_str(), _templateMat, _providers);
}
