#pragma once
#include "ComponentType.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        template <ComponentType ctype>
        struct ComponentType_attribs;

        template <>
        struct ComponentType_attribs<ComponentType::Vertex>
        {
            static const std::string name;
        };

        template <>
        struct ComponentType_attribs<ComponentType::TessControl>
        {
            static const std::string name;
        };

        template <>
        struct ComponentType_attribs<ComponentType::TessEvaluation>
        {
            static const std::string name;
        };

        template <>
        struct ComponentType_attribs<ComponentType::Geometry>
        {
            static const std::string name;
        };

        template <>
        struct ComponentType_attribs<ComponentType::Fragment>
        {
            static const std::string name;
        };

        template <>
        struct ComponentType_attribs<ComponentType::Pseudo>
        {
            static const std::string name;
        };

        template <ComponentType type>
        std::string NameOf()
        {
            return ComponentType_attribs<type>::name;
        }
        std::string NameOf(ComponentType type);
    }
}
