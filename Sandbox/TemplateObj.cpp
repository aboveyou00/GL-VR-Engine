#include "stdafx.h"
#include "TemplateObj.h"
#include "ObjGraphicsObject.h"
#include "DiffuseMaterial.h"
#include "RandomUtils.h"
#include "MatrixStack.h"
#include "AmbientLightSource.h"
#include "PointLightSource.h"
#include "LabControls.h"
#include "LightSourceObject.h"

TemplateObj::TemplateObj(std::string filename, Material * mat, std::vector<IPropertyProvider*> providers, std::function<void(TemplateObj*, float)> tick)
    : createGraphicsObject([filename](TemplateObj* self, GlEngine::GraphicsContext*){ return GlEngine::ObjGraphicsObject::Create(filename.c_str(), self->templateMat, self->providers); }), templateMat(mat), providers(providers), tick(tick)
{
    RequireTick(true);
}
TemplateObj::TemplateObj(std::function<GlEngine::GraphicsObject*(TemplateObj*, GlEngine::GraphicsContext*)> createGraphicsObject, Material * mat, std::vector<IPropertyProvider*> providers, std::function<void(TemplateObj*, float)> tick)
    : createGraphicsObject(createGraphicsObject), templateMat(mat), providers(providers), tick(tick)
{
    RequireTick(true);
}
TemplateObj::~TemplateObj()
{
}

void TemplateObj::Tick(float delta)
{
    tick(this, delta);
}

const char *TemplateObj::name()
{
    return "TemplateObj";
}

GlEngine::GraphicsObject *TemplateObj::CreateGraphicsObject(GlEngine::GraphicsContext *ctx)
{
    return createGraphicsObject(this, ctx);
}
