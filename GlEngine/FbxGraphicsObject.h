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

		bool Initialize() override;
		void Render() override;

	private:
		const char * filename;
	};
}