#include "stdafx.h"
#include "Attribute.h"
#include "Property.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Attribute::Attribute(ComponentArray<std::vector<Snippet>> snippets)
            : snippets(snippets)
        {
        }
        Attribute::Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> fragmentSnippets)
            : snippets({ {}, vertexSnippets, {}, {}, {}, fragmentSnippets, {} })
        {
        }
        Attribute::Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> tessControlSnippets, std::vector<Snippet> tessEvaluationSnippets, std::vector<Snippet> fragmentSnippets)
            : snippets({ {}, vertexSnippets, tessControlSnippets, tessEvaluationSnippets, {}, fragmentSnippets, {} })
        {
        }
        Attribute::Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> tessControlSnippets, std::vector<Snippet> tessEvaluationSnippets, std::vector<Snippet> geometrySnippets, std::vector<Snippet> fragmentSnippets)
            : snippets({ {}, vertexSnippets, tessControlSnippets, tessEvaluationSnippets, geometrySnippets, fragmentSnippets, {} })
        {
        }

        Attribute::~Attribute()
        {
        }
        
        Attribute attr_glPosition = Attribute(
            { // Vertex
                Snippet("[OUT:0] = [IN:0] * [IN:1];", { &prop_ModelViewMatrix, &prop_Position }, { &prop_GlPosition })
            },
            { // Fragment
            }
        );
    }
}