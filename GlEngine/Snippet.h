#pragma once
#include "Property.h"
#include "Component.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		class Snippet
		{
		public:
			Snippet(std::string source, Component* parentComponent);
			~Snippet();

			std::string source;
			Component* parentComponent;
			std::vector<Property*> LocalPropertiesIn;
			std::vector<Property*> LocalPropertiesOut;
		};
	}
}