#include "stdafx.h"
#include "FbxGraphicsObject.h"

#include "FbxLoader.h"

namespace GlEngine
{
	FbxGraphicsObject::FbxGraphicsObject(const char * const filename)
	{
		this->filename = filename;
		subObjects = std::vector<VboGraphicsObject>(10);
	}

	bool FbxGraphicsObject::Initialize()
	{
		if (!GlEngine::FbxLoader::Load(filename, this))
			return false;
		return GraphicsObject::Initialize();
	}

	void FbxGraphicsObject::Render()
	{
		for (int i = 0; i < subObjects.size(); i++)
			subObjects[i].Render();
	}
}