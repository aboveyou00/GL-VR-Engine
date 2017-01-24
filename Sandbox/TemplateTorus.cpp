#include "stdafx.h"
#include "TemplateTorus.h"
#include "ObjGraphicsObject.h"
#include "DiffuseMaterial.h"
#include "RandomUtils.h"
#include "MatrixStack.h"
#include "AmbientLightSource.h"
#include "PointLightSource.h"
#include "LabControls.h"
#include "LightSourceObject.h"

TemplateTorus::TemplateTorus(TemplateMaterial* mat, std::vector<IPropertyProvider*> providers, std::function<void(TemplateTorus*, float)> tick)
    : templateMat(mat), providers(providers), tick(tick)
{
    RequireTick(true);
}
TemplateTorus::~TemplateTorus()
{
}

void TemplateTorus::Tick(float delta)
{
    tick(this, delta);
}

const char *TemplateTorus::name()
{
    return "TemplateTorus";
}

GlEngine::GraphicsObject *TemplateTorus::CreateGraphicsObject(GlEngine::GraphicsContext &ctx)
{
    ctx;
    return GlEngine::ObjGraphicsObject::Create("Resources/torus.obj", templateMat, providers);
}
