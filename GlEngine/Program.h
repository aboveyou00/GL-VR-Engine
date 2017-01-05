#pragma once

#include "ComponentArray.h"
#include "Component.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Component;
        class Attribute;

        class ENGINE_SHARED Program
        {
        public:
            Program(bool useTesselation, bool useGeometry);
            ~Program();

            static const unsigned numComponents = static_cast<unsigned>(std::numeric_limits<ComponentType>::max()) - static_cast<unsigned>(std::numeric_limits<ComponentType>::min()) + 1;
            ComponentArray<Component*> components;

            void AddAttribute(Attribute* attribute);

        private:
            void BootstrapInputs();
            void ResolveProperties();

            ComponentType NextComponentType(unsigned type);
            ComponentType NextComponentType(ComponentType type);
            ComponentType LastComponentType(unsigned type);
            ComponentType LastComponentType(ComponentType type);
        };
    }
}
