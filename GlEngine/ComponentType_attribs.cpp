#include "stdafx.h"
#include "ComponentType_attribs.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        const std::string ComponentType_attribs<ComponentType::Vertex>::name = "Vertex"s;
        const std::string ComponentType_attribs<ComponentType::TessControl>::name = "TessControl"s;
        const std::string ComponentType_attribs<ComponentType::TessEvaluation>::name = "TessEvaluation"s;
        const std::string ComponentType_attribs<ComponentType::Geometry>::name = "Geometry"s;
        const std::string ComponentType_attribs<ComponentType::Fragment>::name = "Fragment"s;
        const std::string ComponentType_attribs<ComponentType::Pseudo>::name = "Pseudo"s;

        std::string NameOf(ComponentType type)
        {
            switch (type)
            {
            case ComponentType::Vertex:
                return "Vertex";
            case ComponentType::TessControl:
                return "TessControl";
            case ComponentType::TessEvaluation:
                return "TessEvaluation";
            case ComponentType::Geometry:
                return "Geometry";
            case ComponentType::Fragment:
                return "Fragment";
            case ComponentType::Pseudo:
                return "***";
            }
            return "";
        }
    }
}
