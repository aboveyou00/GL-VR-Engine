#pragma once

#include "GraphicsObject.h"
#include "VboFactory.h"
#include "VaoFactory.h"

#include "Engine.h"
#include "ServiceProvider.h"
#include "ResourceLoader.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class InstancedGraphicsObject : public GraphicsObject
    {
    public:
        InstancedGraphicsObject(GraphicsObject *gobj)
            : GraphicsObject(false),
              gobj(gobj),
              instances(new VboFactory<type, TArgs...>(BufferMode::Array)),
              instanceCount(0),
              finalized(false),
              queued(false),
              _vao(VaObject())
        {
        }
        ~InstancedGraphicsObject()
        {
            SafeDelete(instances);
        }

        int AddInstance(TArgs... args)
        {
            assert(!finalized && instances != nullptr);
            instanceCount++;
            return instances->AddVertex(args...);
        }

        void Finalize()
        {
            assert(!finalized);
            finalized = true;

            if (*gobj)
            {
                queued = true;
                auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
                resources->QueueResource(this);
            }
        }
        
        bool InitializeGraphics() override
        {
            VaoFactory *vao = VaoFactory::Begin();
            BuildVao(*vao);
            _vao = vao->Compile();

            delete instances;
            instances = nullptr;

            return _vao && GraphicsObject::InitializeGraphics();
        }

        void BuildVao(VaoFactory &vao) override
        {
            if (instances != nullptr)
            {
                gobj->BuildVao(vao);
                vao.AddInstanced(instances);
            }
            else if (_vao) vao.Add(_vao);
        }

        void PreRender(RenderTargetLayer layer) override
        {
            GraphicsObject::PreRender(layer);
            if (*this) _vao.MakeCurrent();
        }
        void RenderImpl(RenderTargetLayer layer) override
        {
            assert(!!*this);
            gobj->RenderInstanced(layer, instanceCount);
        }

        void RenderInstancedImpl(RenderTargetLayer, unsigned) override
        {
            assert(false);
        }

        operator bool() override
        {
            if (finalized && !queued)
            {
                queued = true;
                auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
                resources->QueueResource(this);
            }
            return finalized && _vao && gobj && *gobj;
        }

        const char *name() override
        {
            return "InstancedGraphicsObject<T...>";
        }

    private:
        VaObject _vao;

        bool finalized, queued;
        GraphicsObject *gobj;
        VboFactory<type, TArgs...> *instances;
        int instanceCount;
    };

    template <VboType type>
    class InstancedGraphicsObject<type>;
}
