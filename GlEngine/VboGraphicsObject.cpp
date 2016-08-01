#include "stdafx.h"
#include "VboGraphicsObject.h"
#include "VboFactory.h"

#include "Shader.h"
#include "Texture.h"
#include "OpenGl.h"

namespace GlEngine
{
    VboGraphicsObject::VboGraphicsObject()
        : VboGraphicsObject(VbObject(), VbObject())
	{
	}
    VboGraphicsObject::VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo)
        : VboGraphicsObject(arrayVbo, elementVbo, nullptr, nullptr)
    {
    }
    VboGraphicsObject::VboGraphicsObject(Shader *shader, Texture *texture)
        : VboGraphicsObject(VbObject(), VbObject(), shader, texture)
    {
    }
	VboGraphicsObject::VboGraphicsObject(VbObject arrayVbo, VbObject elementVbo, Shader *shader, Texture *texture)
		: arrayVbo(arrayVbo), elementVbo(elementVbo), shader(shader), texture(texture), verticesFactory(nullptr), trianglesFactory(nullptr)
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
        shader->ShutdownGraphics();
        if (texture != nullptr) texture->ShutdownGraphics();

        arrayVbo.ShutdownGraphics();
        arrayVbo = VbObject();

        elementVbo.ShutdownGraphics();
        elementVbo = VbObject();
    }

    const char *VboGraphicsObject::name()
    {
        return "VboGraphicsObject";
    }

	void VboGraphicsObject::PreRender()
	{
		GraphicsObject::PreRender();
		if (*this)
		{
			arrayVbo.MakeCurrent();
			elementVbo.MakeCurrent();
			if (shader != nullptr && *shader) shader->MakeCurrent();
            if (texture != nullptr && *texture) texture->MakeCurrent();
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
