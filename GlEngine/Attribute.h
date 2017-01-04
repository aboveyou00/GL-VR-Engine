#pragma once

#include "Property.h"
#include "Component.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class AttributeComponent
        {
        public:
            AttributeComponent(std::vector<Property*> constants = std::vector<Property*>(), std::vector<Property*> ins = std::vector<Property*>(), std::vector<Snippet> snippets = std::vector<Snippet>());
            ~AttributeComponent();

            std::vector<Property*> constants;
            std::vector<Property*> ins;

            std::vector<Snippet> snippets;
        };

        class Attribute
        {
        public:
            Attribute(std::vector<Property*> uniforms, std::vector<AttributeComponent> attributeComponents);
            ~Attribute();

            std::vector<Property*> uniforms;
            static const unsigned numComponents = (unsigned)std::numeric_limits<ComponentType>::max() - (unsigned)std::numeric_limits<ComponentType>::min() + 1;
            ComponentArray<AttributeComponent> attributeComponents;
        };

        extern Attribute attr_Position;
        extern Attribute attr_Projection;
        extern Attribute attr_AmbientLight;
    }
}