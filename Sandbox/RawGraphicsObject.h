#pragma once

#include "GraphicsObject.h"
#include "ShaderFactory.h"
#include "RenderTargetLayer.h"
#include "VBOFactory.h"
#include "VboFactoryGraphicsObject.h"

namespace GlEngine
{
    class ObjGraphicsObject;
    class Material;

    namespace ShaderFactory
    {
        class IPropertyProvider;
    }
}

typedef GlEngine::ShaderFactory::ShaderFactory ShaderFactory;
typedef GlEngine::ShaderFactory::IPropertyProvider IPropertyProvider;

class RawGraphicsObject : public GlEngine::GraphicsObject
{
private:
    RawGraphicsObject(GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties);

public:
    template <GlEngine::VboType type, typename... TArgs>
    RawGraphicsObject(GlEngine::VboFactory<type, TArgs...> *vertices, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
        : RawGraphicsObject(shaderSource, properties)
    {
        _compositeObj = new GlEngine::VboFactoryGraphicsObject<type, TArgs...>(vertices, nullptr, createFactory);
    }
    template <GlEngine::VboType type, typename... TArgs>
    RawGraphicsObject(GlEngine::VboFactory<type, TArgs...> *vertices, GlEngine::VboFactory<GlEngine::VboType::UnsignedShort, uint16_t> *faces, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
        : RawGraphicsObject(shaderSource, properties)
    {
        _compositeObj = new GlEngine::VboFactoryGraphicsObject<type, TArgs...>(vertices, faces, createFactory);
    }
    RawGraphicsObject(const char *const filename, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties);
    ~RawGraphicsObject();

    virtual bool Initialize() override;
    virtual void Shutdown() override;
    virtual bool InitializeGraphics() override;
    virtual void ShutdownGraphics() override;

    void SetMaterial(GlEngine::Material *material);

    virtual void AddPropertyProvider(IPropertyProvider *provider) override;
    virtual void RemovePropertyProvider(IPropertyProvider *provider) override;

    virtual void BuildVao(GlEngine::VaoFactory &vao) override;

    virtual void PreRender(GlEngine::RenderTargetLayer layer) override;
    virtual void RenderImpl(GlEngine::RenderTargetLayer layer) override;
    virtual void PostRender(GlEngine::RenderTargetLayer layer) override;

    virtual void PreRenderInstanced(GlEngine::RenderTargetLayer layer) override;
    virtual void RenderInstancedImpl(GlEngine::RenderTargetLayer layer, unsigned instanceCount) override;
    virtual void PostRenderInstanced(GlEngine::RenderTargetLayer layer) override;

    virtual std::string name() override;

    virtual operator bool() override;

private:
    GlEngine::GraphicsObject *_compositeObj;
    std::function<GlEngine::ShaderFactory::ShaderFactory*(GlEngine::Material*)> createFactory;
};
