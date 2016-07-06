#include "stdafx.h"
#include "ObjGraphicsObject.h"

#include "ObjLoader.h"

namespace GlEngine
{
	ObjGraphicsObject::ObjGraphicsObject(const char * const filename)
	{
		this->filename = filename;
	}

	bool ObjGraphicsObject::Initialize()
	{
		if (!GlEngine::ObjLoader::Load(filename, this))
			return false;
		return VboGraphicsObject::Initialize();
	}
}