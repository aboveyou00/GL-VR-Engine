#include "stdafx.h"
#include "VboGraphicsObjectImpl.h"

#include "VboFactory.h"
#include "VboGraphicsSection.h"
#include "VaoFactory.h"

#include "OpenGl.h"

namespace GlEngine
{
    namespace Impl
    {
        VboGraphicsObjectImpl::VboGraphicsObjectImpl(bool instanced)
            : VboGraphicsObjectImpl(VaObject(), instanced)
        {
        }
        VboGraphicsObjectImpl::VboGraphicsObjectImpl(VaObject vao, bool instanced)
            : GraphicsObject(true, instanced),
              _vao(vao),
              finalized(!!vao),
              elemIdx(0),
              currentGraphicsSection(nullptr),
              verticesFactory(finalized ? nullptr : new VboFactory<VboType::Float, Vector<3>, Vector<2>, Vector<3>>(BufferMode::Array)),
              facesFactory(finalized ? nullptr : new VboFactory<VboType::UnsignedShort, uint16_t>(BufferMode::ElementArray))
        {
        }
        VboGraphicsObjectImpl::~VboGraphicsObjectImpl()
        {
            SafeDelete(verticesFactory);
            SafeDelete(facesFactory);
        }

        void VboGraphicsObjectImpl::SetGraphics(Shader *shader, Texture *texture)
        {
            assert(!finalized);
            if (currentGraphicsSection != nullptr && currentGraphicsSection->HasGraphics(shader, texture)) return;
            for (size_t q = 0; q < graphicsSections.size(); q++)
                if (graphicsSections[q]->HasGraphics(shader, texture))
                {
                    currentGraphicsSection = graphicsSections[q];
                    return;
                }
            graphicsSections.push_back(currentGraphicsSection = new Impl::VboGraphicsSection(shader, texture));
        }

        int VboGraphicsObjectImpl::AddVertex(Vector<3> position, Vector<2> texCoord, Vector<3> normal)
        {
            assert(!finalized);
            verticesFactory->AddVertex(position, texCoord, normal, false);
            return elemIdx++;
        }
        void VboGraphicsObjectImpl::AddTriangle(Vector<3, uint16_t> indices)
        {
            assert(!finalized);
            assert(currentGraphicsSection != nullptr);
            for (size_t q = 0; q < 3; q++)
                assert(indices[q] < elemIdx);
            currentGraphicsSection->AddTriangle(indices);
        }
        void VboGraphicsObjectImpl::AddQuad(Vector<4, uint16_t> indices)
        {
            assert(!finalized);
            assert(currentGraphicsSection != nullptr);
            for (size_t q = 0; q < 4; q++)
                assert(indices[q] < elemIdx);
            currentGraphicsSection->AddQuad(indices);
        }

        bool VboGraphicsObjectImpl::Initialize()
        {
            return true;
        }
        void VboGraphicsObjectImpl::Shutdown()
        {
        }
        bool VboGraphicsObjectImpl::InitializeGraphics()
        {
            if (finalized) return false;
            finalized = true;

            if (verticesFactory == nullptr) return false;
            if (facesFactory == nullptr) return false;

            auto vao_factory = VaoFactory::Begin();
            createVao(vao_factory);
            _vao = vao_factory->Compile(); //This will delete vao_factory

            return _vao.InitializeGraphics();
        }
        void VboGraphicsObjectImpl::createVao(VaoFactory *vao)
        {
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->Finalize(facesFactory);

            vao->Add(verticesFactory)
               ->Add(facesFactory);

            delete verticesFactory;
            verticesFactory = nullptr;
            delete facesFactory;
            facesFactory = nullptr;
        }
        void VboGraphicsObjectImpl::ShutdownGraphics()
        {
            _vao.ShutdownGraphics();
            _vao = VaObject();
        }

        const char *VboGraphicsObjectImpl::name()
        {
            return "VboGraphicsObjectImpl";
        }

        void VboGraphicsObjectImpl::PreRender(RenderTargetLayer layer)
        {
            GraphicsObject::PreRender(layer);
            if (*this) _vao.MakeCurrent();
        }
        void VboGraphicsObjectImpl::RenderImpl(RenderTargetLayer layer)
        {
            if (*this)
            {
                if (IsInstanced())
                {
                    auto count = GetInstanceCount();
                    for (size_t q = 0; q < graphicsSections.size(); q++)
                        graphicsSections[q]->RenderInstanced(layer, count);
                }
                else
                {
                    for (size_t q = 0; q < graphicsSections.size(); q++)
                        graphicsSections[q]->Render(layer);
                }
            }
        }

        VboGraphicsObjectImpl::operator bool()
        {
            return finalized && _vao;
        }
    }
}
