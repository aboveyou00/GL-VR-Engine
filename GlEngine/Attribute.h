#pragma once

//#include "Property.h"
//#include "Component.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
<<<<<<< HEAD
		class Attribute
        {
        public:
			Attribute(ComponentArray<std::vector<Snippet>> snippets);
            Attribute(std::vector<std::vector<Snippet>> snippets);
			Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> fragmentSnippets);
			Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> tessControlSnippets, std::vector<Snippet> tessEvaluationSnippets, std::vector<Snippet> fragmentSnippets);
			Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> tessControlSnippets, std::vector<Snippet> tessEvaluationSnippets, std::vector<Snippet> geometrySnippets, std::vector<Snippet> fragmentSnippets);
			~Attribute();

            static const unsigned numComponents = (unsigned)std::numeric_limits<ComponentType>::max() - (unsigned)std::numeric_limits<ComponentType>::min() + 1;
            ComponentArray<std::vector<Snippet>> snippets;
        };

        extern ENGINE_SHARED Attribute attr_glPosition;
        extern ENGINE_SHARED Attribute attr_Projection;
        extern ENGINE_SHARED Attribute attr_AmbientLight;
=======
        //class AttributeComponent
        //{
        //public:
        //    AttributeComponent(std::vector<Property*> constants = std::vector<Property*>(), std::vector<Property*> ins = std::vector<Property*>(), std::vector<Snippet> snippets = std::vector<Snippet>());
        //    ~AttributeComponent();

        //    std::vector<Property*> constants;
        //    std::vector<Property*> ins;

        //    std::vector<Snippet> snippets;
        //};

        //class Attribute
        //{
        //public:
        //    Attribute(std::vector<Property*> uniforms, std::vector<AttributeComponent> attributeComponents);
        //    ~Attribute();

        //    std::vector<Property*> uniforms;
        //    static const unsigned numComponents = static_cast<unsigned>(std::numeric_limits<ComponentType>::max()) - static_cast<unsigned>(std::numeric_limits<ComponentType>::min()) + 1;
        //    ComponentArray<AttributeComponent> attributeComponents;
        //};

        //extern Attribute attr_Position;
        //extern Attribute attr_Projection;
        //extern Attribute attr_AmbientLight;
>>>>>>> 9a332fad24e8f2e4cf0df4e95d7ead07270d041e
    }
}
