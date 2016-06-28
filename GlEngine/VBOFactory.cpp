#include "stdafx.h"
#include "VBOFactory.h"

namespace GlEngine
{
	void VboFactory::Create(unsigned vertexSize)
	{
		if (creating)
			assert(false); // Cannot begin creating again until Compile is called
		creating = true;
		this->vertexSize = vertexSize;
		data.clear();
	}

	void VboFactory::SetMode(GLuint mode)
	{
		currentMode = mode;
	}

	void VboFactory::AddVertex(float * attribs, int count)
	{
		for (int i = 0; i < vertexSize; i++)
		{
			if (i >= count)
				data.push_back(0.f);
			else
				data.push_back(attribs[i]);
		}
	}

	void VboFactory::AddVertex(float * attribs)
	{
		AddVertex(attribs, vertexSize);
	}

	void VboFactory::AddAttrib(int attrib, int start, int size)
	{
		attribs[3 * attribCount] = attrib;
		attribs[3 * attribCount + 1] = start;
		attribs[3 * attribCount + 2] = size;
		attribCount++;
	}

	GLuint VboFactory::Compile()
	{
		glGenBuffers(1, &currentVbo);
		glBufferData(GL_ARRAY_BUFFER, data.size(), &data.front(), GL_STATIC_DRAW);
		for (int i = 0; i < attribCount; i++)
		{
			int name = attribs[3 * i];
			int start = attribs[3 * i + 1];
			int size = attribs[3 * i + 2];
		}
		
		return currentVbo;
	}
}