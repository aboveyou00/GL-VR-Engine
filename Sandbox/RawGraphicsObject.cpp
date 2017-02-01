#include "stdafx.h"
#include "RawGraphicsObject.h"

#include "VboGraphicsSection.h"
#include "RawShaderFactory.h"

typedef GlEngine::ShaderFactory::RawShaderFactory RawShaderFactory;

RawGraphicsObject::RawGraphicsObject(const char * const filename, GlEngine::ShaderFactory::ShaderSource shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*> properties)
    : ObjGraphicsObject(filename), _factory(new RawShaderFactory(shaderSource, properties))
{
}

RawGraphicsObject::~RawGraphicsObject()
{
    delete _factory;
}

bool RawGraphicsObject::Initialize()
{
    ObjGraphicsObject::Initialize();
    for (auto section : graphicsSections)
    {
        section->SetFactory(_factory, providers());
    }
    return true;
}
