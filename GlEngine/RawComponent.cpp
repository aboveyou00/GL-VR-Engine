#include "stdafx.h"
#include "RawComponent.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		RawComponent::RawComponent(ComponentType type, std::string source)
			: Component(type), source(source)
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