#include "stdafx.h"
#include "RawGraphicsObject.h"
#include "ObjGraphicsObject.h"

#include "VboGraphicsSection.h"
#include "RawShaderFactory.h"
#include "Material.h"

typedef GlEngine::ShaderFactory::RawShaderFactory RawShaderFactory;

RawGraphicsObject::RawGraphicsObject(GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
    : GlEngine::GraphicsObject(false)
{
    createFactory = [shaderSource, properties](GlEngine::Material*) { return new RawShaderFactory(shaderSource, properties); };
}
RawGraphicsObject::RawGraphicsObject(const char *const filename, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
    : RawGraphicsObject(shaderSource, properties)
{
    _compositeObj = new GlEngine::ObjGraphicsObject(filename, createFactory);
}
RawGraphicsObject::~RawGraphicsObject()
{
    SafeDelete(_compositeObj);
}

bool RawGraphicsObject::Initialize()
{
    return _compositeObj->Initialize();
}
void RawGraphicsObject::Shutdown()
{
    _compositeObj->Shutdown();
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

void RawGraphicsObject::PreRender(GlEngine::RenderTargetLayer layer)
{
    _compositeObj->PreRender(layer);
}
void RawGraphicsObject::RenderImpl(GlEngine::RenderTargetLayer layer)
{
    _compositeObj->RenderImpl(layer);
}
void RawGraphicsObject::PostRender(GlEngine::RenderTargetLayer layer)
{
    _compositeObj->PostRender(layer);
}

void RawGraphicsObject::PreRenderInstanced(GlEngine::RenderTargetLayer layer)
{
    _compositeObj->PreRenderInstanced(layer);
}
void RawGraphicsObject::RenderInstancedImpl(GlEngine::RenderTargetLayer layer, unsigned instanceCount)
{
    _compositeObj->RenderInstancedImpl(layer, instanceCount);
}
void RawGraphicsObject::PostRenderInstanced(GlEngine::RenderTargetLayer layer)
{
    _compositeObj->PostRenderInstanced(layer);
}

std::string RawGraphicsObject::name()
{
    return "RawGraphicsObject";
}

RawGraphicsObject::operator bool()
{
    return _compositeObj && !!*_compositeObj;
}
