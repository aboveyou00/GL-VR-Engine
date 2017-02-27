#include "stdafx.h"
#include "RawGraphicsObject.h"
#include "ObjGraphicsObject.h"

#include "VboGraphicsSection.h"
#include "RawShaderFactory.h"
#include "Material.h"

typedef GlEngine::ShaderFactory::RawShaderFactory RawShaderFactory;

RawGraphicsObject::RawGraphicsObject(std::string name, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
    : GlEngine::GraphicsObject(name, false)
{
    createFactory = [shaderSource, properties](GlEngine::Material*) { return new RawShaderFactory(shaderSource, properties); };
}
RawGraphicsObject::RawGraphicsObject(std::string name, const char *const filename, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
    : RawGraphicsObject(name, shaderSource, properties)
{
    _compositeObj = new GlEngine::ObjGraphicsObject(name, filename, createFactory);
}
RawGraphicsObject::~RawGraphicsObject()
{
    SafeDelete(_compositeObj);
}

bool RawGraphicsObject::InitializeAsync()
{
    return _compositeObj->InitializeAsync();
}
void RawGraphicsObject::ShutdownAsync()
{
    _compositeObj->ShutdownAsync();
}
bool RawGraphicsObject::InitializeGraphics()
{
    return _compositeObj->InitializeGraphics();
}
void RawGraphicsObject::ShutdownGraphics()
{
    _compositeObj->ShutdownGraphics();
}

void RawGraphicsObject::SetMaterial(GlEngine::Material *material)
{
    auto vbobj = dynamic_cast<GlEngine::Impl::VboFactoryGraphicsObjectImpl*>(_compositeObj);
    assert(vbobj != nullptr);
    vbobj->SetMaterial(material);
}

void RawGraphicsObject::AddPropertyProvider(IPropertyProvider *provider)
{
    _compositeObj->AddPropertyProvider(provider);
}
void RawGraphicsObject::RemovePropertyProvider(IPropertyProvider *provider)
{
    _compositeObj->RemovePropertyProvider(provider);
}

void RawGraphicsObject::BuildVao(GlEngine::VaoFactory &vao)
{
    _compositeObj->BuildVao(vao);
}

void RawGraphicsObject::PreRender(GlEngine::RenderStage* stage)
{
    _compositeObj->PreRender(stage);
}
void RawGraphicsObject::RenderImpl(GlEngine::RenderStage* stage)
{
    _compositeObj->RenderImpl(stage);
}
void RawGraphicsObject::PostRender(GlEngine::RenderStage* stage)
{
    _compositeObj->PostRender(stage);
}

void RawGraphicsObject::PreRenderInstanced(GlEngine::RenderStage* stage)
{
    _compositeObj->PreRenderInstanced(stage);
}
void RawGraphicsObject::RenderInstancedImpl(GlEngine::RenderStage* stage, unsigned instanceCount)
{
    _compositeObj->RenderInstancedImpl(stage, instanceCount);
}
void RawGraphicsObject::PostRenderInstanced(GlEngine::RenderStage* stage)
{
    _compositeObj->PostRenderInstanced(stage);
}

std::string RawGraphicsObject::name()
{
    return "RawGraphicsObject";
}

bool RawGraphicsObject::isReady()
{
    return _compositeObj && _compositeObj->isReady();
}
