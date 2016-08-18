#pragma once

#include "GraphicsObject.h"
#include "VboFactory.h"

namespace GlEngine
{
    template <VboType type, typename... TArgs>
    class InstancedGraphicsObject : public GraphicsObject
    {
    public:
        InstancedGraphicsObject(GraphicsObject *gobj)
            : gobj(gobj),
              instances(new VboFactory<type, TArgs...>(BufferMode::Array)),
              instanceCount(0),
              instanceId(0)
        {
        }
        ~InstancedGraphicsObject()
        {
            SafeDelete(instances);
            SafeDelete(instanceIds);
        }

        int AddInstance(TArgs... args)
        {
            assert(instances != nullptr);
            instanceCount++;
            instances->AddVertex(args...);

            auto id = ++instanceId;
            instanceIds.push_back(id);
            return id;
        }
        bool RemoveInstance(int id)
        {
            auto idx = std::find(instanceIds.begin(), instanceIds.end(), id);
            if (idx == instanceIds.end()) return false;

            auto removeIdx = idx - instanceIds.begin();
            instanceIds.erase(idx);
            instances->RemoveVertex(removeIdx);
            instanceCount--;
            return true;
        }

        bool Initialize() override
        {
            return true;
        }
        void Shutdown() override
        {
        }
        bool InitializeGraphics() override
        {
            return true;
        }
        void ShutdownGraphics() override
        {
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
            return gobj && *gobj;
        }

        const char *name() override
        {
            return "InstancedGraphicsObject<T...>";
        }

    private:
        GraphicsObject *gobj;
        VboFactory<type, TArgs...> *instances;
        std::vector<int> instanceIds;
        int instanceCount;
        unsigned instanceId;
    };

    template <VboType type>
    class InstancedGraphicsObject<type>;
}
