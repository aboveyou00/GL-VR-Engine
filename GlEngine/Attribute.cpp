#include "stdafx.h"
#include "Attribute.h"
#include "Property.h"
#include "Snippet.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        Attribute::Attribute(ComponentArray<std::vector<Snippet*>> snippets)
        {
            std::vector<std::vector<Snippet*>> data;
            for (unsigned i = 0; i < snippets.size(); i++)
                data.push_back(std::vector<Snippet*>());
            this->snippets = ComponentArray<std::vector<Snippet*>>(data);
            
            for (unsigned i = 0; i < this->snippets.size(); i++)
                for (unsigned j = 0; j < snippets[i].size(); j++)
                    this->snippets[i].push_back(snippets[i][j]->Copy());
        }
        Attribute::Attribute(std::vector<Snippet*> vertexSnippets, std::vector<Snippet*> fragmentSnippets)
            : Attribute(ComponentArray<std::vector<Snippet*>>({ {}, vertexSnippets, {}, {}, {}, fragmentSnippets, {} }))
        {
        }
        Attribute::Attribute(std::vector<Snippet*> vertexSnippets, std::vector<Snippet*> tessControlSnippets, std::vector<Snippet*> tessEvaluationSnippets, std::vector<Snippet*> fragmentSnippets)
            : Attribute(ComponentArray<std::vector<Snippet*>>({ {}, vertexSnippets, tessControlSnippets, tessEvaluationSnippets, {}, fragmentSnippets, {} }))
        {
        }
        Attribute::Attribute(std::vector<Snippet*> vertexSnippets, std::vector<Snippet*> tessControlSnippets, std::vector<Snippet*> tessEvaluationSnippets, std::vector<Snippet*> geometrySnippets, std::vector<Snippet*> fragmentSnippets)
            : Attribute(ComponentArray<std::vector<Snippet*>>({ {}, vertexSnippets, tessControlSnippets, tessEvaluationSnippets, geometrySnippets, fragmentSnippets, {} }))
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
                new Snippet("[out:0] = [in:0] * vec4([in:1], 1);", { &prop_ModelViewProjectionMatrix, &prop_Position }, { &prop_GlPosition }),

                //Fallback
                new Snippet("[out:0] = [in:0] * [in:1];", { &prop_ProjectionMatrix, &prop_ModelViewMatrix }, { &prop_ModelViewProjectionMatrix }, SnippetFlag::Fallback)
            },
            { // Fragment
            }
        );

        Attribute attr_DiffuseLight = Attribute(
            { // Vertex
                new Snippet("[out:0] = [in:0] * [in:1] * clamp(dot([in:2], [in:3]), 0.0, 1.0);", { &prop_ReflectionCoefficient, &prop_DiffuseLightColor, &prop_DiffuseLightDirection, &prop_Normal }, { &prop_DiffuseLightColor }),

                //Fallback
                (new Snippet("[temp:0] = [in:1] * [in:0];\n[out:0] = normalize([temp:0] - [in:2]);", { &prop_Position, &prop_ModelViewMatrix, &prop_DiffuseLightPosition }, { &prop_DiffuseLightDirection }, SnippetFlag::Fallback))->WithTemps<Vector<4>>()
            },
            { // Fragment
                new Snippet("[out:0] = [in:0] * [in:1];", { &prop_DiffuseLightColor, &prop_RgbaColor }, { &prop_RgbaColor }, SnippetFlag::Fallback),
                new Snippet("[out:0] = [in:0] * vec4([in:1], 1);", { &prop_DiffuseLightColor, &prop_RgbColor }, { &prop_RgbaColor }, SnippetFlag::Fallback),
                new Snippet("[out:0] = [in:0];", { &prop_DiffuseLightColor }, { &prop_RgbaColor }, SnippetFlag::Fallback)
            }
        );
    }
}
