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

        void AddLine(unsigned idx0, unsigned idx1);
        void AddTriangle(unsigned idx0, unsigned idx1, unsigned idx2);
        void AddQuad(unsigned idx0, unsigned idx1, unsigned idx2, unsigned idx3);
        void AddLine(Vector<2, uint16_t> indices);
        void AddTriangle(Vector<3, uint16_t> indices);
        void AddQuad(Vector<4, uint16_t> indices);

        virtual bool InitializeAsync() override;
        virtual void ShutdownAsync() override;
        virtual bool InitializeGraphics() override;
        virtual void ShutdownGraphics() override;

        virtual void PreRender(RenderStage* stage) override;
        virtual void RenderImpl(RenderStage* stage) override;
        virtual void PostRender(RenderStage* stage) override;

        virtual void PreRenderInstanced(RenderStage* stage) override;
        virtual void RenderInstancedImpl(RenderStage* stage, unsigned instanceCount) override;
        virtual void PostRenderInstanced(RenderStage* stage) override;

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
