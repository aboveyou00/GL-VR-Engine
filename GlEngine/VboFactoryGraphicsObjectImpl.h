#pragma once

#include "GraphicsObject.h"
#include "VaObject.h"
#include "RenderTargetLayer.h"
#include "vbo_element_t.h"

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
        VboFactoryGraphicsObjectImpl(std::string name, bool allowFaces, array_index_t elemIdx, VaObject vao, CreateFactoryFn createFactory = [](Material*) { return nullptr; });
        ~VboFactoryGraphicsObjectImpl();

        virtual void AddPropertyProvider(ShaderFactory::IPropertyProvider *provider) override;
        virtual void RemovePropertyProvider(ShaderFactory::IPropertyProvider *provider) override;

        void SetMaterial(Material *material);
        virtual void PrepareShaderFactory(ShaderFactory::ShaderFactory *factory) = 0;

        void AddLine(array_index_t idx0, array_index_t idx1);
        void AddTriangle(array_index_t idx0, array_index_t idx1, array_index_t idx2);
        void AddQuad(array_index_t idx0, array_index_t idx1, array_index_t idx2, array_index_t idx3);
        void AddLine(Vector<2, array_index_t> indices);
        void AddTriangle(Vector<3, array_index_t> indices);
        void AddQuad(Vector<4, array_index_t> indices);

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
        array_index_t elemIdx;
    };
}
