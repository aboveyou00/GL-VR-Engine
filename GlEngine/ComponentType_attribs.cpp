#include "stdafx.h"
#include "ComponentType_attribs.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        const std::string ComponentType_attribs<ComponentType::Input>::name = NameOf(ComponentType::Input);
        const std::string ComponentType_attribs<ComponentType::Vertex>::name = NameOf(ComponentType::Vertex);
        const std::string ComponentType_attribs<ComponentType::TessControl>::name = NameOf(ComponentType::TessControl);
        const std::string ComponentType_attribs<ComponentType::TessEvaluation>::name = NameOf(ComponentType::TessEvaluation);
        const std::string ComponentType_attribs<ComponentType::Geometry>::name = NameOf(ComponentType::Geometry);
        const std::string ComponentType_attribs<ComponentType::Fragment>::name = NameOf(ComponentType::Fragment);
        const std::string ComponentType_attribs<ComponentType::Output>::name = NameOf(ComponentType::Output);

        std::string NameOf(ComponentType type)
        {
            switch (type)
            {
            case ComponentType::Input:
                return "INPUT>>>";
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
            case ComponentType::Output:
                return ">>>OUTPUT";
            }
            return "";
        }
    }
}
