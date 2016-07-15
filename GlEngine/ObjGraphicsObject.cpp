#include "stdafx.h"
#include "ObjGraphicsObject.h"

#include "ObjLoader.h"

#include <unordered_map>

namespace GlEngine
{
	ObjGraphicsObject::ObjGraphicsObject(const char *const filename)
	{
		this->filename = filename;
	}

    ObjGraphicsObject *ObjGraphicsObject::Create(const char *name)
    {
        static std::unordered_map<const char*, ObjGraphicsObject*> cache;
        auto ptr = cache[name];
        if (ptr == nullptr) ptr = cache[name] = new ObjGraphicsObject(name);
        return ptr;
    }

	bool ObjGraphicsObject::Initialize()
	{
		if (!GlEngine::ObjLoader::Load(filename, this))
			return false;
		return VboGraphicsObject::Initialize();
	}
}
