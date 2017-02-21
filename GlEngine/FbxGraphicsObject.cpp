#include "stdafx.h"
#include "FbxGraphicsObject.h"
#include "FbxLoader.h"
#include <sstream>

namespace GlEngine
{
    FbxGraphicsObject::FbxGraphicsObject(std::string name, const char *const filename)
        : VboGraphicsObject(name), filename(filename), initialized(false)
    {
    }
    FbxGraphicsObject::~FbxGraphicsObject()
    {
    }

    FbxGraphicsObject *FbxGraphicsObject::Create(std::string name, const char* filename)
    {
        static std::unordered_map<const char*, FbxGraphicsObject*> cache;
        auto ptr = cache[filename];
        if (ptr == nullptr) ptr = cache[filename] = new FbxGraphicsObject(name, filename);
        return ptr;
    }

    bool FbxGraphicsObject::InitializeAsync()
    {
        if (!FbxLoader::Load(filename, this)) return false;
        return VboGraphicsObject::InitializeAsync();
    }

    //std::string FbxGraphicsObject::name()
    //{
    //    std::stringstream stream;
    //    stream << "FbxGraphicsObject(" << filename << ")";
    //    return stream.str();
    //}
}
