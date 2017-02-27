#include "stdafx.h"
#include "VboFactoryGraphicsObjectImpl.h"
#include "VaoFactory.h"
#include "ShaderFactory.h"
#include "VboGraphicsSection.h"

namespace GlEngine::Impl
{
    VboFactoryGraphicsObjectImpl::VboFactoryGraphicsObjectImpl(std::string name, bool allowFaces, unsigned elemIdx, VaObject vao, CreateFactoryFn createFactory)
        : GraphicsObject(name, true),
          allowFaces(allowFaces),
          _vao(vao),
          finalized(vao.isReady()),
          elemIdx(elemIdx),
          currentGraphicsSection(nullptr),
          createFactory(createFactory)
    {
    }
    VboFactoryGraphicsObjectImpl::~VboFactoryGraphicsObjectImpl()
    {
    }

    void VboFactoryGraphicsObjectImpl::AddPropertyProvider(ShaderFactory::IPropertyProvider *provider)
    {
        ScopedLock _lock(mutex);
        GraphicsObject::AddPropertyProvider(provider);
        for (size_t q = 0; q < graphicsSections.size(); q++)
            graphicsSections[q]->factory().AddPropertyProviders(provider);
    }
    void VboFactoryGraphicsObjectImpl::RemovePropertyProvider(ShaderFactory::IPropertyProvider *provider)
    {
        ScopedLock _lock(mutex);
        GraphicsObject::RemovePropertyProvider(provider);
        for (size_t q = 0; q < graphicsSections.size(); q++)
            graphicsSections[q]->factory().RemovePropertyProviders(provider);
    }

    void VboFactoryGraphicsObjectImpl::SetMaterial(Material *material)
    {
        ScopedLock _lock(mutex);
        assert(!finalized);
        assert(allowFaces || !currentGraphicsSection);
        if (currentGraphicsSection != nullptr && currentGraphicsSection->GetMaterial() == material) return;
        for (size_t q = 0; q < graphicsSections.size(); q++)
            if (graphicsSections[q]->GetMaterial() == material)
            {
                currentGraphicsSection = graphicsSections[q];
                return;
            }
        currentGraphicsSection = new VboGraphicsSection(material, providers(), createFactory(material));
        auto *newFactory = &currentGraphicsSection->factory();
        PrepareShaderFactory(newFactory);
        graphicsSections.push_back(currentGraphicsSection);
    }

    void VboFactoryGraphicsObjectImpl::AddTriangle(unsigned idx0, unsigned idx1, unsigned idx2)
    {
        AddTriangle({ idx0, idx1, idx2 });
    }
    void VboFactoryGraphicsObjectImpl::AddQuad(unsigned idx0, unsigned idx1, unsigned idx2, unsigned idx3)
    {
        AddQuad({ idx0, idx1, idx2, idx3 });
    }
    void VboFactoryGraphicsObjectImpl::AddTriangle(Vector<3, uint16_t> indices)
    {
        ScopedLock _lock(mutex);
        assert(!finalized);
        assert(allowFaces);
        assert(currentGraphicsSection != nullptr);
        for (size_t q = 0; q < 3; q++)
            assert(indices[q] < elemIdx);
        currentGraphicsSection->AddTriangle(indices);
    }
    void VboFactoryGraphicsObjectImpl::AddQuad(Vector<4, uint16_t> indices)
    {
        ScopedLock _lock(mutex);
        assert(!finalized);
        assert(allowFaces);
        assert(currentGraphicsSection != nullptr);
        for (size_t q = 0; q < 4; q++)
            assert(indices[q] < elemIdx);
        currentGraphicsSection->AddQuad(indices);
    }

    bool VboFactoryGraphicsObjectImpl::InitializeAsync()
    {
        return GraphicsObject::InitializeAsync();
    }
    void VboFactoryGraphicsObjectImpl::ShutdownAsync()
    {
        GraphicsObject::ShutdownAsync();
    }
    bool VboFactoryGraphicsObjectImpl::InitializeGraphics()
    {
        if (!GraphicsObject::InitializeGraphics()) return false;
        if (finalized) return false;
        finalized = true;

        auto vao_factory = VaoFactory::Begin();
        BuildVao(*vao_factory);
        _vao = vao_factory->Compile(); //This will delete vao_factory

        return _vao.InitializeGraphics();
    }
    void VboFactoryGraphicsObjectImpl::ShutdownGraphics()
    {
        GraphicsObject::ShutdownGraphics();
        _vao.ShutdownGraphics();
        _vao = VaObject();
    }

    void VboFactoryGraphicsObjectImpl::PreRender(RenderStage* stage)
    {
        ScopedLock _lock(mutex);
        GraphicsObject::PreRender(stage);
        if (this->isReady()) _vao.MakeCurrent();
    }
    void VboFactoryGraphicsObjectImpl::RenderImpl(RenderStage* stage)
    {
        ScopedLock _lock(mutex);
        if (allowFaces)
        {
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->Render(stage);
        }
        else
        {
            if (!currentGraphicsSection || !*currentGraphicsSection) return;
            currentGraphicsSection->RenderPoints(stage, elemIdx);
        }
    }
    void VboFactoryGraphicsObjectImpl::PostRender(RenderStage* stage)
    {
        GraphicsObject::PostRender(stage);
    }

    void VboFactoryGraphicsObjectImpl::PreRenderInstanced(RenderStage* stage)
    {
        GraphicsObject::PreRenderInstanced(stage);
    }
    void VboFactoryGraphicsObjectImpl::RenderInstancedImpl(RenderStage* stage, unsigned instanceCount)
    {
        ScopedLock _lock(mutex);
        for (size_t q = 0; q < graphicsSections.size(); q++)
            graphicsSections[q]->RenderInstanced(stage, instanceCount);
    }
    void VboFactoryGraphicsObjectImpl::PostRenderInstanced(RenderStage* stage)
    {
        GraphicsObject::PostRenderInstanced(stage);
    }

    std::string VboFactoryGraphicsObjectImpl::name()
    {
        return "VboFactoryGraphicsObject";
    }

    bool VboFactoryGraphicsObjectImpl::isReady()
    {
        return finalized && _vao.isReady();
    }
}
