#include "stdafx.h"
#include "Attribute.h"
#include "Property.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Attribute::Attribute(ComponentArray<std::vector<Snippet>> snippets)
        {
            std::vector<std::vector<Snippet*>> data;
            for (unsigned i = 0; i < snippets.size(); i++)
                data.push_back(std::vector<Snippet*>());
            this->snippets = ComponentArray<std::vector<Snippet*>>(data);
            
            for (unsigned i = 0; i < this->snippets.size(); i++)
                for (unsigned j = 0; j < snippets[i].size(); j++)
                    this->snippets[i].push_back(snippets[i][j].Copy());
        }
        Attribute::Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> fragmentSnippets)
            : Attribute(ComponentArray<std::vector<Snippet>>({ {}, vertexSnippets, {}, {}, {}, fragmentSnippets, {} }))
        {
        }
        Attribute::Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> tessControlSnippets, std::vector<Snippet> tessEvaluationSnippets, std::vector<Snippet> fragmentSnippets)
            : Attribute(ComponentArray<std::vector<Snippet>>({ {}, vertexSnippets, tessControlSnippets, tessEvaluationSnippets, {}, fragmentSnippets, {} }))
        {
        }
        Attribute::Attribute(std::vector<Snippet> vertexSnippets, std::vector<Snippet> tessControlSnippets, std::vector<Snippet> tessEvaluationSnippets, std::vector<Snippet> geometrySnippets, std::vector<Snippet> fragmentSnippets)
            : Attribute(ComponentArray<std::vector<Snippet>>({ {}, vertexSnippets, tessControlSnippets, tessEvaluationSnippets, geometrySnippets, fragmentSnippets, {} }))
        {
        }

        Attribute::~Attribute()
        {
            for (unsigned i = 0; i < this->snippets.size(); i++)
                for (unsigned j = 0; j < snippets[i].size(); j++)
                    delete this->snippets[i][j];
        }
        
        Attribute attr_GlPosition = Attribute(
            { // Vertex
                Snippet("[out:0] = [in:0] * vec4([in:1], 1);", { &prop_ModelViewProjectionMatrix, &prop_Position }, { &prop_GlPosition })
            },
            { // Fragment
            }
        );

        Attribute attr_DiffuseLight = Attribute(
            { // Vertex
                Snippet("[out:0] = clamp(dot([in:0], [in:1]), 0.0, 1.0);", { &prop_DiffuseLightDirection, &prop_Normal }, { &prop_DiffuseLightIntensity }),
                Snippet("[out:0] = [in:0] * [in:1];", { &prop_DiffuseLightIntensity, &prop_DiffuseLightColor }, { &prop_DiffuseLight })
            },
            { // Fragment
                Snippet("[out:0] = [in:0]", { &prop_DiffuseLight }, { &prop_RgbaColor })
            }
        );
    }
}