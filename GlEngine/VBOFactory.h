#pragma once

#include "OpenGl.h"
#include "Vector.h"

#include <vector>

namespace GlEngine
{
	class VboFactory
	{
	public:
		void Create(unsigned vertexSize);
		void SetMode(GLuint mode);
		void AddVertex(float * attribs, int count);
		void AddVertex(float * attribs);
		void AddAttrib(int attrib, int start, int size);
		GLuint Compile();

	private:
		bool creating = false;
		unsigned vertexSize = 0;

		GLuint currentVbo;
		GLuint currentMode;

		static const int maxAttribs = 32;
		int attribs[3 * maxAttribs];
		int attribCount = 0;
		std::vector<float> data;
	};
}