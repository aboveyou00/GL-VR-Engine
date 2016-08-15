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
            : Impl::VboGraphicsObjectImpl(vao),
              instancesFactory(finalized ? nullptr : new VboFactory<VboType::Float, TArgs...>())
        {
        }
        ~VboGraphicsObject()
        {
            SafeDelete(instancesFactory);
        }

        void AddInstance(TArgs... args)
        {
            assert(!finalized);
            assert(instancesFactory != nullptr);
            instancesFactory->AddVertex(args...);
        }

        const char *name() override
        {
            return "VboGraphicsObject<T...>";
        }

    protected:
        void createVao(VaoFactory *vao) override
        {
            Impl::VboGraphicsObjectImpl::createVao(vao);
            if (instancesFactory != nullptr)
            {
                vao->Add(instancesFactory);
                delete instancesFactory;
                instancesFactory = nullptr;
            }
        }

    private:
        VboFactory<VboType::Float, TArgs...> *instancesFactory;
	};

    template <>
    const char *VboGraphicsObject<>::name()
    {
        return "VboGraphicsObject";
    }

    template <>
    VboGraphicsObject<>::VboGraphicsObject(VaObject vao)
        : Impl::VboGraphicsObjectImpl(vao),
          instancesFactory(nullptr)
    {
    }
}
