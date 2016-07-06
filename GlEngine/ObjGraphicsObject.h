#pragma once

#include "VboGraphicsObject.h"

namespace GlEngine
{
	class ENGINE_SHARED ObjGraphicsObject : public VboGraphicsObject
	{
	public:
		ObjGraphicsObject() : VboGraphicsObject() {}
		ObjGraphicsObject(const char * const filename);

		bool Initialize() override;

	private:
		const char * filename;
	};
}