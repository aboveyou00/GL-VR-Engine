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
    RawGraphicsObject(std::string name, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties);

public:
    template <GlEngine::VboType type, typename... TArgs>
    RawGraphicsObject(std::string name, GlEngine::VboFactory<type, TArgs...> *vertices, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
        : RawGraphicsObject(name, shaderSource, properties)
    {
        _compositeObj = new GlEngine::VboFactoryGraphicsObject<type, TArgs...>(name, vertices, nullptr, createFactory);
    }
    template <GlEngine::VboType type, typename... TArgs>
    RawGraphicsObject(std::string name, GlEngine::VboFactory<type, TArgs...> *vertices, GlEngine::VboFactory<GlEngine::VboType::UnsignedShort, uint16_t> *faces, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties)
        : RawGraphicsObject(name, shaderSource, properties)
    {
        _compositeObj = new GlEngine::VboFactoryGraphicsObject<type, TArgs...>(name, vertices, faces, createFactory);
    }
    RawGraphicsObject(std::string name, const char *const filename, GlEngine::ShaderFactory::ShaderSource* shaderSource, std::map<size_t, GlEngine::ShaderFactory::ShaderProp*>* properties);
    ~RawGraphicsObject();

    virtual bool InitializeAsync() override;
    virtual void ShutdownAsync() override;
    virtual bool InitializeGraphics() override;
    virtual void ShutdownGraphics() override;

    void SetMaterial(GlEngine::Material *material);

    virtual void AddPropertyProvider(IPropertyProvider *provider) override;
    virtual void RemovePropertyProvider(IPropertyProvider *provider) override;

    virtual void BuildVao(GlEngine::VaoFactory &vao) override;

    virtual void PreRender(GlEngine::RenderStage* stage) override;
    virtual void RenderImpl(GlEngine::RenderStage* stage) override;
    virtual void PostRender(GlEngine::RenderStage* stage) override;

    virtual void PreRenderInstanced(GlEngine::RenderStage* stage) override;
    virtual void RenderInstancedImpl(GlEngine::RenderStage* stage, unsigned instanceCount) override;
    virtual void PostRenderInstanced(GlEngine::RenderStage* stage) override;

    virtual std::string name() override;

    virtual bool isReady() override;

private:
    GlEngine::GraphicsObject *_compositeObj;
    std::function<GlEngine::ShaderFactory::ShaderFactory*(GlEngine::Material*)> createFactory;
};
