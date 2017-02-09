#include "stdafx.h"
#include "TemplateMaterialFactory.h"
#include "TemplateMaterial.h"

TemplateMaterialFactory::TemplateMaterialFactory()
    : finalized(false)
{
}
TemplateMaterialFactory::~TemplateMaterialFactory()
{
}

TemplateMaterial *TemplateMaterialFactory::Create()
{
    finalized = true;
    return new TemplateMaterial(this);
}

TemplateMaterialFactory *TemplateMaterialFactory::Name(std::string name)
{
    assert(!finalized);
    this->_name = name;
    return this;
}
TemplateMaterialFactory *TemplateMaterialFactory::Attribute(GlEngine::ShaderFactory::Attribute *attr)
{
    assert(!finalized);
    this->_attrs.push_back(attr);
    return this;
}
TemplateMaterialFactory *TemplateMaterialFactory::Await(GlEngine::IGraphicsComponent *c)
{
    assert(!finalized);
    if (std::find(_awaiting.begin(), _awaiting.end(), c) == _awaiting.end()) _awaiting.push_back(c);
    return this;
}
