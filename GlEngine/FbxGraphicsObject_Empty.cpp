#include "stdafx.h"
#include "FbxGraphicsObject.h"

namespace GlEngine
{
    FbxGraphicsObject<>::FbxGraphicsObject(const char *const filename)
        : filename(filename), initialized(false)
    {
    }
    FbxGraphicsObject<>::~FbxGraphicsObject()
    {
    }

    FbxGraphicsObject<> *FbxGraphicsObject<>::Create(const char* name)
    {
        static std::unordered_map<const char*, FbxGraphicsObject<>*> cache;
        auto ptr = cache[name];
        if (ptr == nullptr) ptr = cache[name] = new FbxGraphicsObject<>(name);
        return ptr;
    }

    bool FbxGraphicsObject<>::Initialize()
    {
        if (!Impl::FbxGraphicsObjectImpl::SharedInitialize(this, filename)) return false;
        return VboGraphicsObject<>::Initialize();
    }

    const char *FbxGraphicsObject<>::name()
    {
        return "FbxGraphicsObject";
    }
}
