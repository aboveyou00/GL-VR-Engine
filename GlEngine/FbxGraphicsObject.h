#pragma once

#include "VboGraphicsObject.h"

namespace GlEngine
{
	class ENGINE_SHARED FbxGraphicsObject : public GraphicsObject
	{
	public:
		FbxGraphicsObject() {}
		FbxGraphicsObject(const char * const filename);

		std::vector<VboGraphicsObject*> subObjects;
		std::vector<VboGraphicsObject*> pending;
		rt_mutex pendingMutex;

		static FbxGraphicsObject* Create(const char* name);
		void Render() override;
		void AddSubObject(VboGraphicsObject* graphicsObject);

		bool Initialize() override;
		void Shutdown() override;
		bool InitializeGraphics() override;
		void ShutdownGraphics() override;

		operator bool() override;

		const char * name() override;

	private:
		const char * filename;
		bool initialized;
		void ProcessPending();
	};
}