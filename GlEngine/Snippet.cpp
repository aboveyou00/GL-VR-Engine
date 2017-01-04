#include "stdafx.h"
#include "Snippet.h"

#include "StringUtils.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		Snippet::Snippet(std::string source, std::vector<Property*> localPropertiesIn, std::vector<Property*> localPropertiesOut)
			: source(source), localPropertiesIn(localPropertiesIn), localPropertiesOut(localPropertiesOut)
		{
			// [OUT:0] = [IN:0] 
		}
		Snippet::~Snippet()
		{
		}
	}
}