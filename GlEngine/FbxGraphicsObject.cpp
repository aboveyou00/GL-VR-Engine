#include "stdafx.h"
#include "FbxGraphicsObject.h"
#include "FbxLoader.h"
#include <sstream>

namespace GlEngine
{

    FbxGraphicsObject::FbxGraphicsObject(const char *const filename)
        : filename(filename), initialized(false)
    {
    }
    FbxGraphicsObject::~FbxGraphicsObject()
    {
    }

    FbxGraphicsObject *FbxGraphicsObject::Create(const char* name)
    {
        static std::unordered_map<const char*, FbxGraphicsObject*> cache;
        auto ptr = cache[name];
        if (ptr == nullptr) ptr = cache[name] = new FbxGraphicsObject(name);
        return ptr;
    }

    bool FbxGraphicsObject::InitializeAsync()
    {
        if (!FbxLoader::Load(filename, this)) return false;
        return VboGraphicsObject::InitializeAsync();
    }

    std::string FbxGraphicsObject::name()
    {
        std::stringstream stream;
        stream << "FbxGraphicsObject(" << filename << ")";
        return stream.str();
    }
}
