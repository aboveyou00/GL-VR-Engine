#include "stdafx.h"
#include "FbxGraphicsObject.h"

#include "FbxLoader.h"
#include <unordered_map>

namespace GlEngine
{
	FbxGraphicsObject::FbxGraphicsObject(const char * const filename)
	{
		this->filename = filename;
		subObjects = std::vector<VboGraphicsObject>(10);
		initialized = false;
	}

	FbxGraphicsObject *FbxGraphicsObject::Create(const char *name)
	{
		static std::unordered_map<const char*, FbxGraphicsObject*> cache;
		auto ptr = cache[name];
		if (ptr == nullptr) ptr = cache[name] = new FbxGraphicsObject(name);
		return ptr;
	}

	bool FbxGraphicsObject::Initialize()
	{
		if (!GlEngine::FbxLoader::Load(filename, this))
			return false;
		ProcessPending();
		for (size_t i = 0; i < subObjects.size(); i++)
			subObjects[i].Initialize();

		initialized = true;
		return GraphicsObject::Initialize();
	}

	void FbxGraphicsObject::AddSubObject(VboGraphicsObject graphicsObject)
	{
		ScopedLock _lock(pendingMutex);
		pending.push_back(graphicsObject);
	}

	void FbxGraphicsObject::ProcessPending()
	{
		ScopedLock _lock(pendingMutex);
		for (size_t i = 0; i < pending.size(); i++)
		{
			subObjects.push_back(pending[i]);
			if (initialized)
				pending[i].Initialize();
		}
		pending.clear();
	}

	void FbxGraphicsObject::Render()
	{
		ProcessPending();
		for (size_t i = 0; i < subObjects.size(); i++)
			subObjects[i].Render();
	}
}