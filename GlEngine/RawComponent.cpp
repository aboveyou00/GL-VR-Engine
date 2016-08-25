#include "stdafx.h"
#include "RawComponent.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		RawComponent::RawComponent(std::string source)
			: source(source)
		{
		}
		RawComponent::~RawComponent()
		{
		}
		std::string RawComponent::Compile()
		{
			return source;
		}
	}
}