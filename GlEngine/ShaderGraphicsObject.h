#pragma once

#include "EngineShared.h"
#include "Shader.h"
#include "GraphicsObject.h"

namespace GlEngine
{
	class ENGINE_SHARED ShaderGraphicsObject : public GraphicsObject
	{
	public:
		ShaderGraphicsObject() : ShaderGraphicsObject(Shader("Shaders", "simple")) {};
		ShaderGraphicsObject(Shader shader);
		~ShaderGraphicsObject();

		bool Initialize() override;
		void Shutdown() override;

		Shader shader;
		
		void PreRender() override;
};
}
