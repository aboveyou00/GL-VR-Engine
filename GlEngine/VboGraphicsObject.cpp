#include "stdafx.h"
#include "VboGraphicsObject.h"

#include "VboFactory.h"
#include "VboGraphicsSection.h"
#include "VaoFactory.h"

#include "OpenGl.h"

namespace GlEngine
{
    VboGraphicsObject::VboGraphicsObject()
        : VboGraphicsObject(VaObject())
    {
    }
    VboGraphicsObject::VboGraphicsObject(VaObject vao)
        : GraphicsObject(true),
          _vao(vao),
          finalized(!!vao),
          elemIdx(0),
          currentGraphicsSection(nullptr),
          verticesFactory(finalized ? nullptr : new VboFactory<VboType::Float, Vector<3>, Vector<2>, Vector<3>>(BufferMode::Array)),
          facesFactory(finalized ? nullptr : new VboFactory<VboType::UnsignedShort, uint16_t>(BufferMode::ElementArray))
    {
    }
    VboGraphicsObject::~VboGraphicsObject()
    {
        SafeDelete(verticesFactory);
        SafeDelete(facesFactory);
    }

    void VboGraphicsObject::SetMaterial(Material *material)
    {
        ScopedLock _lock(mutex);
        assert(!finalized);
        if (currentGraphicsSection != nullptr && currentGraphicsSection->GetMaterial() == material) return;
        for (size_t q = 0; q < graphicsSections.size(); q++)
            if (graphicsSections[q]->GetMaterial() == material)
            {
                currentGraphicsSection = graphicsSections[q];
                return;
            }
        graphicsSections.push_back(currentGraphicsSection = new Impl::VboGraphicsSection(material));
    }

    int VboGraphicsObject::AddVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal)
    {
        assert(!finalized);
        verticesFactory->AddVertex(position, texCoord, normal, false);
        return elemIdx++;
    }
    void VboGraphicsObject::AddTriangle(Vector<3, uint16_t> indices)
    {
        ScopedLock _lock(mutex);
        assert(!finalized);
        assert(currentGraphicsSection != nullptr);
        for (size_t q = 0; q < 3; q++)
            assert(indices[q] < elemIdx);
        currentGraphicsSection->AddTriangle(indices);
    }
    void VboGraphicsObject::AddQuad(Vector<4, uint16_t> indices)
    {
        ScopedLock _lock(mutex);
        assert(!finalized);
        assert(currentGraphicsSection != nullptr);
        for (size_t q = 0; q < 4; q++)
            assert(indices[q] < elemIdx);
        currentGraphicsSection->AddQuad(indices);
    }

    bool VboGraphicsObject::Initialize()
    {
        return true;
    }
    void VboGraphicsObject::Shutdown()
    {
    }
    bool VboGraphicsObject::InitializeGraphics()
    {
        if (finalized) return false;
        finalized = true;

        if (verticesFactory == nullptr) return false;
        if (facesFactory == nullptr) return false;

        auto vao_factory = VaoFactory::Begin();
        BuildVao(*vao_factory);
        _vao = vao_factory->Compile(); //This will delete vao_factory

        return _vao.InitializeGraphics();
    }
    void VboGraphicsObject::BuildVao(VaoFactory &vao)
    {
        if (verticesFactory != nullptr && facesFactory != nullptr)
        {
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->Finalize(facesFactory);

            vao.Add(verticesFactory)
               .Add(facesFactory);

            delete verticesFactory;
            verticesFactory = nullptr;
            delete facesFactory;
            facesFactory = nullptr;
        }
        else if (_vao) vao.Add(_vao);
    }
    void VboGraphicsObject::ShutdownGraphics()
    {
        _vao.ShutdownGraphics();
        _vao = VaObject();
    }

    const char *VboGraphicsObject::name()
    {
        return "VboGraphicsObject";
    }

    void VboGraphicsObject::PreRender(RenderTargetLayer layer)
    {
        GraphicsObject::PreRender(layer);
        if (*this) _vao.MakeCurrent();
    }
    void VboGraphicsObject::RenderImpl(RenderTargetLayer layer)
    {
        ScopedLock _lock(mutex);
        for (size_t q = 0; q < graphicsSections.size(); q++)
            graphicsSections[q]->Render(layer);
    }

    void VboGraphicsObject::RenderInstancedImpl(RenderTargetLayer layer, unsigned instanceCount)
    {
        ScopedLock _lock(mutex);
        for (size_t q = 0; q < graphicsSections.size(); q++)
            graphicsSections[q]->RenderInstanced(layer, instanceCount);
    }

    VboGraphicsObject::operator bool()
    {
        return finalized && _vao;
    }
}
