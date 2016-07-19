#include "stdafx.h"
#include "VboGraphicsObject.h"
#include "VboFactory.h"

#include "OpenGl.h"

namespace GlEngine
{
    VboGraphicsObject::VboGraphicsObject()
        : VboGraphicsObject(VbObject(), VbObject())
	{
	}
	VboGraphicsObject::VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo)
		: arrayVbo(arrayVbo), elementVbo(elementVbo), shader("Shaders", "direct_light"), verticesFactory(nullptr), trianglesFactory(nullptr)
	{
	}
	VboGraphicsObject::VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo, Shader shader)
		: shader(shader), arrayVbo(arrayVbo), elementVbo(elementVbo), verticesFactory(nullptr), trianglesFactory(nullptr)
	{
	}
	VboGraphicsObject::~VboGraphicsObject()
	{
	}

	bool VboGraphicsObject::Initialize()
	{
		return true;
	}
    void VboGraphicsObject::Shutdown()
    {
    }
    bool VboGraphicsObject::InitializeGraphics()
    {
        if (!arrayVbo)
        {
            if (verticesFactory == nullptr) return false;
            arrayVbo = verticesFactory->Compile();
            delete verticesFactory;
        }
        if (!elementVbo)
        {
            if (trianglesFactory == nullptr) return false;
            elementVbo = trianglesFactory->Compile();
            delete trianglesFactory;
        }

        if (!arrayVbo.InitializeGraphics())
            return false;
        if (!elementVbo.InitializeGraphics())
            return false;

        return true;
    }
    void VboGraphicsObject::ShutdownGraphics()
    {
        arrayVbo.ShutdownGraphics();
        arrayVbo = VbObject();

        elementVbo.ShutdownGraphics();
        elementVbo = VbObject();
    }

	void VboGraphicsObject::PreRender()
	{
		GraphicsObject::PreRender();
		if (*this)
		{
			arrayVbo.MakeCurrent();
			elementVbo.MakeCurrent();
			if (shader) shader.MakeCurrent();
		}
	}

	void VboGraphicsObject::Render()
	{
		GraphicsObject::Render();
		if (*this) glDrawElements(GL_TRIANGLES, triCount * 3, static_cast<GLenum>(VboType::UnsignedShort), nullptr);
	}

    VboGraphicsObject::operator bool()
    {
        return arrayVbo && elementVbo;
    }
}
