#pragma once

#include "Component.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		class ENGINE_SHARED Program
		{
		public:
			Program(bool useTesselation, bool useGeometry);
			~Program();

			static const int numComponents = (unsigned)std::numeric_limits<ComponentType>::max() - (unsigned)std::numeric_limits<ComponentType>::min() + 1;
			ComponentArray components;

			void AddUniform(Property* property);
			void AddIn(ComponentType type, Property* property);
			void AddOut(ComponentType type, Property* property);
			void AddSnippet(ComponentType type, Snippet* snippet);
		};
	}
}