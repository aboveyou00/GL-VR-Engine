#include "stdafx.h"
#include "VboGraphicsObject.h"

#include "OpenGl.h"
#include "VBOFactory.h"

namespace GlEngine
{
    VboGraphicsObject::VboGraphicsObject()
        : VboGraphicsObject(VbObject(), VbObject())
	{
	}
	VboGraphicsObject::VboGraphicsObject(VbObject arryaVbo, VbObject elementVbo)
		: arrayVbo(arrayVbo), elementVbo(elementVbo)
	{
		shader = Shader("Shaders", "direct_light");
	}
	VboGraphicsObject::VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo, Shader shader)
		: shader(shader), arrayVbo(arrayVbo), elementVbo(elementVbo)
	{
	}
	VboGraphicsObject::~VboGraphicsObject()
	{
	}

	bool VboGraphicsObject::Initialize()
	{
		if (!shader.Initialize())
			return false;
		if (!arrayVbo.Initialize())
			return false;
		if (!elementVbo.Initialize())
			return false;

		return true;
	}

	void VboGraphicsObject::Shutdown()
	{
		arrayVbo.Shutdown();
		arrayVbo = VbObject();

		elementVbo.Shutdown();
		elementVbo = VbObject();
	}

	void VboGraphicsObject::PreRender()
	{
		if (arrayVbo)
		{
			arrayVbo.MakeCurrent();
			if (shader)
				shader.MakeCurrent();
			if (elementVbo)
				elementVbo.MakeCurrent();
		}
	}

	void VboGraphicsObject::Render()
	{
		GraphicsObject::Render();
		if (arrayVbo && elementVbo)
		{
			glDrawElements(GL_TRIANGLES, triCount * 3, static_cast<GLenum>(VboType::UnsignedShort), nullptr);
		}
	}
}
