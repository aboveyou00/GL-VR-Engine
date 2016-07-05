#pragma once

#include "ShaderGraphicsObject.h"
#include "VbObject.h"

namespace GlEngine
{
	class ENGINE_SHARED VboGraphicsObject : public ShaderGraphicsObject
	{
	public:
		VboGraphicsObject();
		~VboGraphicsObject();

		VbObject arrayVbo;
		VbObject elementVbo;

		bool Initialize() override;
		void Shutdown() override;

		void PreRender() override;
		void Render() override;
	};
}
