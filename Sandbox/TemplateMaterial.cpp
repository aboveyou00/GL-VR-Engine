#include "stdafx.h"
#include "TemplateMaterial.h"
#include "TemplateMaterialFactory.h"

#include "Shader.h"
#include "ShaderFactory.h"
#include "Property.h"
#include "Attribute.h"

#include "StringUtils.h"
#include <sstream>

TemplateMaterial::TemplateMaterial(TemplateMaterialFactory *factory)
    : _factory(factory)
{
}
TemplateMaterial::~TemplateMaterial()
{
    if (_factory != nullptr)
    {
        delete _factory;
        _factory = nullptr;
    }
}

TemplateMaterialFactory *TemplateMaterial::Factory()
{
    return new TemplateMaterialFactory();
}

void TemplateMaterial::Push(ShaderFactory &factory)
{
    for (size_t q = 0; q < _factory->_pushFns.size(); q++)
        _factory->_pushFns[q](this, factory);
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
    return _factory->_props;
}
std::vector<GlEngine::ShaderFactory::Attribute*> TemplateMaterial::attributes()
{
    return _factory->_attrs;
}

std::string TemplateMaterial::name()
{
    std::stringstream stream;
    if (GlEngine::Util::is_empty_or_ws(_factory->_name)) stream << "TemplateMaterial {";
    else stream << _factory->_name << "(TemplateMaterial) {";
    for (auto *attr : _factory->_attrs)
        stream << " " << attr->name();
    stream << " }";
    return stream.str();
}
TemplateMaterial::operator bool()
{
    for (size_t q = 0; q < _factory->_awaiting.size(); q++)
        if (!_factory->_awaiting[q] || !*_factory->_awaiting[q]) return false;
    return true;
}
