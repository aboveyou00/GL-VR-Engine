#pragma once

#include "VboGraphicsObjectImpl.h"
#include "VaoFactory.h"

namespace GlEngine
{
    template <typename... TArgs>
    class VboGraphicsObject : public Impl::VboGraphicsObjectImpl
    {
    public:
        VboGraphicsObject()
            : VboGraphicsObject(VaObject())
        {
        }
        VboGraphicsObject(VaObject vao)
            : Impl::VboGraphicsObjectImpl(vao, true),
              instancesFactory(finalized ? nullptr : new VboFactory<VboType::Float, TArgs...>(BufferMode::Array)),
              instanceCount(0),
              instanceId(0)
        {
        }
        ~VboGraphicsObject()
        {
            SafeDelete(instancesFactory);
        }

        int AddInstance(TArgs... args)
        {
            assert(instancesFactory != nullptr);
            instanceCount++;
            instancesFactory->AddVertex(args...);

            auto id = ++instanceId;
            instanceIds.push_back(id);
            return id;
        }
        bool RemoveInstance(int id)
        {
            auto idx = std::find(instanceIds.begin(), instanceIds.end(), id);
            if (idx == instanceIds.end()) return false;

            unsigned offset = idx - instanceIds.begin();
            instanceIds.erase(idx);
            instancesFactory->RemoveVertex(offset);
            instanceCount--;
            return true;
        }

        const char *name() override
        {
            return "VboGraphicsObject<T...>";
        }

    protected:
        void createVao(VaoFactory *vao) override
        {
            Impl::VboGraphicsObjectImpl::createVao(vao);
            if (instancesFactory != nullptr) vao->Add(instancesFactory);
        }

    private:
        VboFactory<VboType::Float, TArgs...> *instancesFactory;
        std::vector<int> instanceIds;
        unsigned instanceCount, instanceId;
    };

    template <>
    class ENGINE_SHARED VboGraphicsObject<> : public Impl::VboGraphicsObjectImpl
    {
    public:
        VboGraphicsObject();
        VboGraphicsObject(VaObject vao);
        ~VboGraphicsObject();

        const char *name() override;
    };
}
