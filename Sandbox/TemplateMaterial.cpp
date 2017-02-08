#include "stdafx.h"
#include "TemplateMaterial.h"
#include "Shader.h"

#include "ShaderFactory.h"
#include "Property.h"
#include "Attribute.h"
#include <sstream>

TemplateMaterial::TemplateMaterial(std::vector<ShaderProp*> props, std::vector<Attribute*> attribs, std::function<void(TemplateMaterial*, ShaderFactory&)> push)
    : props(props), attribs(attribs), push(push)
{
}
TemplateMaterial::~TemplateMaterial()
{
}

void TemplateMaterial::Push(ShaderFactory &factory)
{
    push(this, factory);
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

std::string TemplateMaterial::name()
{
    std::stringstream stream;
    stream << "TemplateMaterial {";
    //for (auto *attr : attribs)
    //    stream << " " << attr->name();
    stream << " }";
    return stream.str();
}
TemplateMaterial::operator bool()
{
    return true;
}
