#pragma once

#include "ObjGraphicsObject.h"
#include "ShaderFactory.h"

typedef GlEngine::ShaderFactory::ShaderFactory ShaderFactory;

class RawGraphicsObject : public GlEngine::ObjGraphicsObject
{
public:
    RawGraphicsObject(const char * const filename, GlEngine::ShaderFactory::ShaderSource shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*> properties);
    ~RawGraphicsObject();

    virtual bool Initialize() override;

private:
    ShaderFactory* _factory;
};