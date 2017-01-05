#pragma once

#include "ComponentArray.h"
#include "Component.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Component;
        class Attribute;
        class PropertySource;

        class ENGINE_SHARED Program
        {
        public:
            Program(bool useTesselation, bool useGeometry);
            ~Program();

            static const unsigned numComponents = static_cast<unsigned>(std::numeric_limits<ComponentType>::max()) - static_cast<unsigned>(std::numeric_limits<ComponentType>::min()) + 1;
            ComponentArray<Component*> components;

            void AddPropertySource(PropertySource *propSource);
            void AddAttribute(Attribute* attribute);

            void Compile();

        private:
            void BootstrapInputs();
            void ResolveProperties();

            ComponentType NextComponentType(unsigned type);
            ComponentType NextComponentType(ComponentType type);
            ComponentType LastComponentType(unsigned type);
            ComponentType LastComponentType(ComponentType type);

            std::vector<PropertySource*> propSources;
            bool compilationStarted = false;
        };
    }
}
