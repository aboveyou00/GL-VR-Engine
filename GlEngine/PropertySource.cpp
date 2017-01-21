#include "stdafx.h"
#include "PropertySource.h"
#include "FactoryUtils.h"
#include "ShaderProp.h"

namespace GlEngine
{
    namespace ShaderFactory
    {
        PropertySource::PropertySource(PropertySourceFlag flags, std::vector<ComponentType> supportedComponents)
            : flags(flags), supportedComponents(supportedComponents)
        {
            assert(supportedComponents.size() > 0);
        }
        PropertySource::~PropertySource()
        {
        }

        const std::vector<ShaderProp*> PropertySource::inProperties()
        {
            return std::vector<ShaderProp*>();
        }

        std::string PropertySource::PropertyName(ShaderProp * prop)
        {
            return prop->name;
        }

        bool PropertySource::HasFlag(PropertySourceFlag flag) const
        {
            return (flags & flag) != PropertySourceFlag::None;
        }
        void PropertySource::SetFlag(PropertySourceFlag flag, bool val)
        {
            if (val) flags |= flag;
            else flags &= ~flag;
        }
        void PropertySource::SetFlag(PropertySourceFlag flag)
        {
            SetFlag(flag, true);
        }
        void PropertySource::ResetFlag(PropertySourceFlag flag)
        {
            SetFlag(flag, false);
        }

        std::vector<ComponentType> PropertySource::componentsEarliest()
        {
            std::vector<ComponentType> components;
            for (ComponentType type = ComponentType::Vertex; type <= ComponentType::Fragment; type++)
                if (std::find(supportedComponents.begin(), supportedComponents.end(), type) != supportedComponents.end())
                    components.push_back(type);
            return components;
        }

        std::vector<ComponentType> PropertySource::componentsLatest()
        {
            std::vector<ComponentType> components;
            for (ComponentType type = ComponentType::Fragment; type >= ComponentType::Vertex; type--)
                if (std::find(supportedComponents.begin(), supportedComponents.end(), type) != supportedComponents.end())
                    components.push_back(type);
            return components;
        }

        std::vector<ComponentType> PropertySource::componentsDefault()
        {
            return supportedComponents;
        }

        bool PropertySource::noSideEffects() const
        {
            return HasFlag(PropertySourceFlag::NoSideEffects);
        }
        bool PropertySource::hasSideEffects() const
        {
            return !HasFlag(PropertySourceFlag::NoSideEffects);
        }
    }
}
