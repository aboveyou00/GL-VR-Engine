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
        InstancedGraphicsObject(std::string name, GraphicsObject *gobj, ShaderFactory::Property<TArgs>*... props)
            : GraphicsObject(name, false),
              gobj(gobj),
              instances(VboFactory<type, TArgs...>::CreateArray(props...)),
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

            if (gobj != nullptr && gobj->isReady())
            {
                queued = true;
                auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
                resources->QueueInitialize(this);
            }
        }

        virtual bool InitializeGraphics() override
        {
            VaoFactory *vao = VaoFactory::Begin();
            BuildVao(*vao);
            _vao = vao->Compile();

            delete instances;
            instances = nullptr;

            return _vao.isReady() && GraphicsObject::InitializeGraphics();
        }

        void BuildVao(VaoFactory &vao) override
        {
            if (instances != nullptr)
            {
                gobj->BuildVao(vao);
                vao.AddInstanced(instances);
            }
            else if (_vao.isReady()) vao.Add(_vao);
        }

        void PreRender(RenderStage *stage) override
        {
            GraphicsObject::PreRender(stage);
            if (this->isReady()) _vao.MakeCurrent();
        }
        void RenderImpl(RenderStage *stage) override
        {
            assert(this->isReady());
            gobj->RenderInstanced(stage, instanceCount);
        }
        void PostRender(RenderStage *stage) override
        {
            GraphicsObject::PostRender(stage);
        }

        void RenderInstancedImpl(RenderStage*, unsigned) override
        {
            assert(false);
        }

        virtual bool isReady() override
        {
            if (finalized && !queued)
            {
                queued = true;
                auto resources = Engine::GetInstance().GetServiceProvider().GetService<ResourceLoader>();
                resources->QueueInitialize(this);
            }
            return finalized && _vao.isReady() && gobj != nullptr && gobj->isReady();
        }

        virtual std::string name() override
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
