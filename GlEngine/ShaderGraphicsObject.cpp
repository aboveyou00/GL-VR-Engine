#include "stdafx.h"
#include "ShaderGraphicsObject.h"

namespace GlEngine
{
	ShaderGraphicsObject::ShaderGraphicsObject()
	{
	}
	ShaderGraphicsObject::~ShaderGraphicsObject()
	{
	}

	bool ShaderGraphicsObject::Initialize()
	{
		if (!shader)
		{
			shader = Shader("Shaders", "simple");
			if (!shader.Initialize()) return false;
		}
		return true;
	}

	void ShaderGraphicsObject::Shutdown()
	{
		shader.Shutdown();
	}

	void ShaderGraphicsObject::PreRender()
	{
		if (shader)
			shader.MakeCurrent();
	}
}
