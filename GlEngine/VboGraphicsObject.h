#pragma once

#include "ShaderGraphicsObject.h"
#include "VbObject.h"

namespace GlEngine
{
	class ENGINE_SHARED VboGraphicsObject : public GraphicsObject
	{
	public:
		VboGraphicsObject();
		VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo);
		VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo, Shader shader);
		~VboGraphicsObject();

		VbObject arrayVbo;
		VbObject elementVbo;
		Shader shader;

		int triCount;
		int quadCount;

		bool Initialize() override;
		void Shutdown() override;

		void PreRender() override;
		void Render() override;
	};
}
