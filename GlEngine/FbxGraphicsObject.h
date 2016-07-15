#pragma once

#include "VboGraphicsObject.h"

namespace GlEngine
{
	class ENGINE_SHARED FbxGraphicsObject : public GraphicsObject
	{
	public:
		FbxGraphicsObject() {}
		FbxGraphicsObject(const char * const filename);

		std::vector<VboGraphicsObject> subObjects;
		std::vector<VboGraphicsObject> pending;
		rt_mutex pendingMutex;

		static FbxGraphicsObject* Create(const char* name);
		bool Initialize() override;
		void Render() override;
		void AddSubObject(VboGraphicsObject graphicsObject);

	private:
		const char * filename;
		bool initialized;
		void ProcessPending();
	};
}