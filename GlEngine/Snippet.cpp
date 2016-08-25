#include "stdafx.h"
#include "Snippet.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		Snippet::Snippet(std::string source, std::vector<Property*> localPropertiesIn, std::vector<Property*> localPropertiesOut)
			: source(source), localPropertiesIn(localPropertiesIn), localPropertiesOut(localPropertiesOut)
		{
		}
		Snippet::~Snippet()
		{
		}
	}
}