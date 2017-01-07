#pragma once

#include "ComponentArray.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        class ENGINE_SHARED Attribute
        {
        public:
            Attribute(ComponentArray<std::vector<Snippet>> snippets);
            Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> fragmentSnippets);
            Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> tessControlSnippets, std::vector<Snippet> tessEvaluationSnippets, std::vector<Snippet> fragmentSnippets);
            Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> tessControlSnippets, std::vector<Snippet> tessEvaluationSnippets, std::vector<Snippet> geometrySnippets, std::vector<Snippet> fragmentSnippets);
            ~Attribute();

            static const unsigned numComponents = (unsigned)std::numeric_limits<ComponentType>::max() - (unsigned)std::numeric_limits<ComponentType>::min() + 1;
            ComponentArray<std::vector<Snippet*>> snippets;
        };

        extern ENGINE_SHARED Attribute attr_GlPosition;
        extern ENGINE_SHARED Attribute attr_AmbientLight;
        extern ENGINE_SHARED Attribute attr_DiffuseLight;
    }
}
