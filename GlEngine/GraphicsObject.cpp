#include "stdafx.h"
#include "GraphicsObject.h"

#include "OpenGl.h"
#include "VBOFactory.h"

namespace GlEngine
{
	GraphicsObject::GraphicsObject()
	{
	}
	GraphicsObject::~GraphicsObject()
	{
	}

	bool GraphicsObject::Initialize()
	{
		return true;
	}

    void GraphicsObject::Shutdown()
    {
	}

	void GraphicsObject::PreRender()
	{
	}

	void GraphicsObject::Render()
	{
		PreRender();
	}
}
