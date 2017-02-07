#include "stdafx.h"
#include "RawGraphicsObject.h"

#include "VboGraphicsSection.h"
#include "RawShaderFactory.h"
#include "Material.h"

typedef GlEngine::ShaderFactory::RawShaderFactory RawShaderFactory;

RawGraphicsObject::RawGraphicsObject(const char * const filename, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
    : ObjGraphicsObject(filename, [shaderSource, properties](GlEngine::Material*) { return new RawShaderFactory(shaderSource, properties); })
{
}

RawGraphicsObject::~RawGraphicsObject()
{
}
