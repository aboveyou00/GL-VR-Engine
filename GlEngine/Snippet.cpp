#include "stdafx.h"
#include "Snippet.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		Snippet::Snippet(std::string source, Component* parentComponent)
			: source(source), parentComponent(parentComponent)
		{
		}
		Snippet::~Snippet()
		{
		}
	}
}