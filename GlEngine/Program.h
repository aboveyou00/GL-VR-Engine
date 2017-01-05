#pragma once

#include "ComponentArray.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Component;
        class Attribute;
        class Property;
        class Snippet;

        class ENGINE_SHARED Program
        {
        public:
            Program(bool useTesselation, bool useGeometry);
            ~Program();

            static const unsigned numComponents = static_cast<unsigned>(std::numeric_limits<ComponentType>::max()) - static_cast<unsigned>(std::numeric_limits<ComponentType>::min()) + 1;
            ComponentArray<Component*> components;

<<<<<<< HEAD
            void AddAttribute(Attribute* attribute);
=======
            //void AddAttribute(Attribute* attribute);
            //
            //void AddConstant(ComponentType type, Property* property);
            //void AddUniform(Property* property);
            //void AddIn(ComponentType type, Property* property);
            //void AddOut(ComponentType type, Property* property);
            //void AddSnippet(ComponentType type, Snippet* snippet);
>>>>>>> 9a332fad24e8f2e4cf0df4e95d7ead07270d041e

        private:
			void ResolveProperties();

            ComponentType NextComponentType(unsigned type);
            ComponentType NextComponentType(ComponentType type);
            ComponentType LastComponentType(unsigned type);
            ComponentType LastComponentType(ComponentType type);
        };
    }
}
