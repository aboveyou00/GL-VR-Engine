#pragma once

#include "Component.h"
#include "Attribute.h"

namespace GlEngine
{
	namespace ShaderFactory
	{
		class ENGINE_SHARED Program
		{
		public:
			Program(bool useTesselation, bool useGeometry);
			~Program();

			Matrix<10, 100> mat;

			static const unsigned numComponents = (unsigned)std::numeric_limits<ComponentType>::max() - (unsigned)std::numeric_limits<ComponentType>::min() + 1;
			ComponentArray<Component*> components;

			void AddAttribute(Attribute* attribute);
			
			void AddConstant(ComponentType type, Property* property);
			void AddUniform(Property* property);
			void AddIn(ComponentType type, Property* property);
			void AddOut(ComponentType type, Property* property);
			void AddSnippet(ComponentType type, Snippet* snippet);

		private:
			ComponentType NextComponentType(unsigned type);
			ComponentType NextComponentType(ComponentType type);
			ComponentType LastComponentType(unsigned type);
			ComponentType LastComponentType(ComponentType type);
		};
	}
}