#pragma once

#include "ComponentArray.h"
#include "Component.h"
#include <map>

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
            int FindUniform(ShaderProp* prop);
            unsigned FindOrCreateUniform(ShaderProp* prop);
            void ConnectComponentsProperty(unsigned firstIndex, unsigned lastIndex, ShaderProp* prop);

            ShaderSource *Compile();

            void WriteToDisk(std::string name);

        private:
            void BootstrapInputs();
            void BootstrapOutputs();

            void ResolveProperties();

            std::map<unsigned, ShaderProp*> uniforms;
            std::vector<PropertySource*> propSources;
            bool compilationStarted = false;
        };
    }
}
