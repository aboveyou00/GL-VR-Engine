#pragma once

#include "GraphicsObject.h"
#include "VaObject.h"
#include "RenderTargetLayer.h"

namespace GlEngine
{
    class Material;

    typedef std::function<ShaderFactory::ShaderFactory*(Material*)> CreateFactoryFn;
}

namespace GlEngine::Impl
{
    class VboGraphicsSection;

    class ENGINE_SHARED VboFactoryGraphicsObjectImpl : public GraphicsObject
    {
    public:
        VboFactoryGraphicsObjectImpl(std::string name, bool allowFaces, unsigned elemIdx, VaObject vao, CreateFactoryFn createFactory = [](Material*) { return nullptr; });
        ~VboFactoryGraphicsObjectImpl();

        virtual void AddPropertyProvider(ShaderFactory::IPropertyProvider *provider) override;
        virtual void RemovePropertyProvider(ShaderFactory::IPropertyProvider *provider) override;

        void SetMaterial(Material *material);
        virtual void PrepareShaderFactory(ShaderFactory::ShaderFactory *factory) = 0;

        void AddTriangle(unsigned idx0, unsigned idx1, unsigned idx2);
        void AddQuad(unsigned idx0, unsigned idx1, unsigned idx2, unsigned idx3);
        void AddTriangle(Vector<3, uint16_t> indices);
        void AddQuad(Vector<4, uint16_t> indices);

        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual void PreRender(RenderTargetLayer layer) override;
        virtual void RenderImpl(RenderTargetLayer layer) override;
        virtual void PostRender(RenderTargetLayer layer) override;

        virtual void PreRenderInstanced(RenderTargetLayer layer) override;
        virtual void RenderInstancedImpl(RenderTargetLayer layer, unsigned instanceCount) override;
        virtual void PostRenderInstanced(RenderTargetLayer layer) override;

        virtual std::string name() override;

        virtual bool isReady() override;

    protected:
        VaObject _vao;
        bool finalized, allowFaces;

        rt_mutex mutex;
        
        std::vector<VboGraphicsSection*> graphicsSections;
        VboGraphicsSection *currentGraphicsSection;
        CreateFactoryFn createFactory;
        int elemIdx;
    };
}
