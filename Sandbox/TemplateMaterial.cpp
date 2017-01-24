#include "stdafx.h"
#include "TemplateMaterial.h"
#include "Shader.h"

#include "ShaderFactory.h"
#include "Property.h"
#include "Attribute.h"

TemplateMaterial::TemplateMaterial(std::vector<ShaderProp*> props, std::vector<Attribute*> attribs, std::function<void(ShaderFactory&)> push)
    : props(props), attribs(attribs), push(push)
{
}
TemplateMaterial::~TemplateMaterial()
{
}

void TemplateMaterial::Push(ShaderFactory &factory)
{
    push(factory);
}

bool TemplateMaterial::IsOpaque()
{
    return true;
}

TesselationType TemplateMaterial::GetTesselationType()
{
    return TesselationType::Disabled;
}

std::vector<GlEngine::ShaderFactory::ShaderProp*> TemplateMaterial::properties()
{
    return props;
}
std::vector<GlEngine::ShaderFactory::Attribute*> TemplateMaterial::attributes()
{
    return attribs;
}

const char *TemplateMaterial::name()
{
    return "TemplateMaterial";
}
TemplateMaterial::operator bool()
{
    return true;
}
