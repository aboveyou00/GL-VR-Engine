#pragma once

#include "VboGraphicsObject.h"
#include "FbxGraphicsObjectImpl.h"
#include <unordered_map>

namespace GlEngine
{
    template <typename... TArgs>
	class FbxGraphicsObject : public VboGraphicsObject<TArgs...>
	{
    private:
        FbxGraphicsObject(const char *const filename)
            : filename(filename), initialized(false)
        {
        }
        ~FbxGraphicsObject()
        {
        }

	public:
        static FbxGraphicsObject<TArgs...> *Create(const char* name)
        {
            static std::unordered_map<const char*, FbxGraphicsObject<TArgs...>*> cache;
            auto ptr = cache[name];
            if (ptr == nullptr) ptr = cache[name] = new FbxGraphicsObject<TArgs...>(name);
            return ptr;
        }
		
		bool Initialize() override
        {
            if (!Impl::FbxGraphicsObjectImpl::SharedInitialize(this, filename)) return false;
            return VboGraphicsObject<TArgs...>::Initialize();
        }

        const char *name() override
        {
            return "FbxGraphicsObject<T...>";
        }

	private:
		const char *filename;
		bool initialized;
	};

    template <>
    class ENGINE_SHARED FbxGraphicsObject<> : public VboGraphicsObject<>
    {
    private:
        FbxGraphicsObject(const char *const filename);
        ~FbxGraphicsObject();

    public:
        static FbxGraphicsObject<> *Create(const char* name);

        bool Initialize() override;

        const char *name() override;

    private:
        const char *filename;
        bool initialized;
    };
}
