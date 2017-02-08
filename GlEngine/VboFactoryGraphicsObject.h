#pragma once

#include "GraphicsObject.h"
#include "VaObject.h"
#include "RenderTargetLayer.h"
#include "VaoFactory.h"
#include "ShaderFactory.h"

#include "VboGraphicsSection.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class VboFactory;
    class Material;

    namespace Impl
    {
        class VboGraphicsSection;
    }

    typedef std::function<ShaderFactory::ShaderFactory*(Material*)> CreateFactoryFn;

    template <VboType type, typename... TArgs>
    class VboFactoryGraphicsObject : public GraphicsObject
    {
    public:
        typedef VboFactory<type, TArgs...> TFactory;
        typedef VboFactory<VboType::UnsignedShort, uint16_t> TFacesFactory;

        VboFactoryGraphicsObject(TFactory *vertices, TFacesFactory *faces = nullptr, CreateFactoryFn createFactory = [](Material*) { return nullptr; })
            : VboFactoryGraphicsObject(VaObject(), vertices, faces, createFactory)
        {
        }
        VboFactoryGraphicsObject(VaObject vao, TFactory *vertices = nullptr, TFacesFactory *faces = nullptr, CreateFactoryFn createFactory = [](Material*) { return nullptr; })
            : GraphicsObject(true),
              _vao(vao),
              finalized(!!vao),
              elemIdx(0),
              currentGraphicsSection(nullptr),
              _verticesFactory(vertices),
              _facesFactory(faces),
              createFactory(createFactory)
        {
            if (finalized)
            {
                assert(!_verticesFactory);
                assert(!_facesFactory);
            }
            else
            {
                assert(_verticesFactory && _verticesFactory->mode() == BufferMode::Array);
                assert(!_facesFactory || _facesFactory->mode() == BufferMode::ElementArray);
            }
        }
        ~VboFactoryGraphicsObject()
        {
            SafeDelete(_verticesFactory);
            SafeDelete(_facesFactory);
        }

        virtual void AddPropertyProvider(ShaderFactory::IPropertyProvider *provider) override
        {
            ScopedLock _lock(mutex);
            GraphicsObject::AddPropertyProvider(provider);
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->factory().AddPropertyProviders(provider);
        }
        virtual void RemovePropertyProvider(ShaderFactory::IPropertyProvider *provider) override
        {
            ScopedLock _lock(mutex);
            GraphicsObject::RemovePropertyProvider(provider);
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->factory().RemovePropertyProviders(provider);
        }

        void SetMaterial(Material *material)
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
            graphicsSections.push_back(currentGraphicsSection = new Impl::VboGraphicsSection(material, providers(), createFactory(material)));
        }

        virtual int AddVertex(TArgs... args)
        {
            assert(!finalized);
            _verticesFactory->AddVertex(args..., false);
            return elemIdx++;
        }
        inline void AddTriangle(unsigned idx0, unsigned idx1, unsigned idx2)
        {
            AddTriangle({ idx0, idx1, idx2 });
        }
        inline void AddQuad(unsigned idx0, unsigned idx1, unsigned idx2, unsigned idx3)
        {
            AddQuad({ idx0, idx1, idx2, idx3 });
        }
        void AddTriangle(Vector<3, uint16_t> indices)
        {
            ScopedLock _lock(mutex);
            assert(!finalized);
            assert(currentGraphicsSection != nullptr);
            for (size_t q = 0; q < 3; q++)
                assert(indices[q] < elemIdx);
            currentGraphicsSection->AddTriangle(indices);
        }
        void AddQuad(Vector<4, uint16_t> indices)
        {
            ScopedLock _lock(mutex);
            assert(!finalized);
            assert(currentGraphicsSection != nullptr);
            for (size_t q = 0; q < 4; q++)
                assert(indices[q] < elemIdx);
            currentGraphicsSection->AddQuad(indices);
        }

        virtual bool Initialize() override
        {
            return GraphicsObject::Initialize();
        }
        virtual void Shutdown() override
        {
            GraphicsObject::Shutdown();
        }
        virtual bool InitializeGraphics() override
        {
            if (!GraphicsObject::InitializeGraphics()) return false;
            if (finalized) return false;
            finalized = true;

            if (_verticesFactory == nullptr) return false;

            auto vao_factory = VaoFactory::Begin();
            BuildVao(*vao_factory);
            _vao = vao_factory->Compile(); //This will delete vao_factory

            return _vao.InitializeGraphics();
        }
        virtual void ShutdownGraphics() override
        {
            GraphicsObject::ShutdownGraphics();
            _vao.ShutdownGraphics();
            _vao = VaObject();
        }

        virtual void BuildVao(VaoFactory &vao) override
        {
            if (_verticesFactory != nullptr)
            {
                if (_facesFactory != nullptr)
                {
                    for (size_t q = 0; q < graphicsSections.size(); q++)
                        graphicsSections[q]->Finalize(_facesFactory);

                    vao.Add(_verticesFactory)
                       .Add(_facesFactory);

                    SafeDelete(_verticesFactory);
                    SafeDelete(_facesFactory);
                }
                else
                {
                    assert(false);
                }
            }
            else if (_vao) vao.Add(_vao);
        }

        virtual void PreRender(RenderTargetLayer layer) override
        {
            ScopedLock _lock(mutex);
            GraphicsObject::PreRender(layer);
            if (*this) _vao.MakeCurrent();
        }
        virtual void RenderImpl(RenderTargetLayer layer) override
        {
            ScopedLock _lock(mutex);
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->Render(layer);
        }
        virtual void PostRender(RenderTargetLayer layer) override
        {
            GraphicsObject::PostRender(layer);
        }

        virtual void PreRenderInstanced(RenderTargetLayer layer) override
        {
            GraphicsObject::PreRenderInstanced(layer);
        }
        virtual void RenderInstancedImpl(RenderTargetLayer layer, unsigned instanceCount) override
        {
            ScopedLock _lock(mutex);
            for (size_t q = 0; q < graphicsSections.size(); q++)
                graphicsSections[q]->RenderInstanced(layer, instanceCount);
        }
        virtual void PostRenderInstanced(RenderTargetLayer layer) override
        {
            GraphicsObject::PostRenderInstanced(layer);
        }

        virtual std::string name() override
        {
            return "VboFactoryGraphicsObject";
        }

        virtual operator bool() override
        {
            return finalized && _vao;
        }

    protected:
        bool finalized;
        rt_mutex mutex;
        std::vector<Impl::VboGraphicsSection*> graphicsSections;
        CreateFactoryFn createFactory;

    private:
        Impl::VboGraphicsSection *currentGraphicsSection;
        int elemIdx;

        VaObject _vao;
        TFactory *_verticesFactory;
        TFacesFactory *_facesFactory;
    };
}
