#include "stdafx.h"
#include "FbxGraphicsObject.h"

#include "FbxLoader.h"
#include <unordered_map>

#include "Font.h"

namespace GlEngine
{
	FbxGraphicsObject::FbxGraphicsObject(const char * const filename)
	{
		this->filename = filename;
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

		//for (unsigned i = 0; i < subObjects.size(); i++)
		//	if (!subObjects[i]->Initialize())
		//		return false;
		
		return GraphicsObject::Initialize();
	}
	void FbxGraphicsObject::Shutdown()
	{
	}
	bool FbxGraphicsObject::InitializeGraphics()
	{
		ProcessPending();
		//for (size_t i = 0; i < subObjects.size(); i++)
		//	subObjects[i]->InitializeGraphics();

		initialized = true;
		return GraphicsObject::InitializeGraphics();
	}
	void FbxGraphicsObject::ShutdownGraphics()
	{
	}

	FbxGraphicsObject::operator bool()
	{
		return subObjects.size() > 0;
	}

	const char * FbxGraphicsObject::name()
	{
		return "FbxGraphicsObject";
	}

	void FbxGraphicsObject::AddSubObject(VboGraphicsObject* graphicsObject)
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
			//if (initialized)
			//	pending[i]->Initialize();
		}
		pending.clear();
	}

    void FbxGraphicsObject::PreRender()
    {
        GraphicsObject::PreRender();
        ProcessPending();
    }
	void FbxGraphicsObject::RenderImpl()
	{
		for (size_t i = 0; i < subObjects.size(); i++)
			subObjects[i]->Render();

		//static auto font = Font("font.otf", 32);
		//font.Render("Hello world!");
	}
}
