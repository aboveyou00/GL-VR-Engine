#pragma once

#include "ComponentArray.h"
#include "Component.h"
#include "ShaderFactoryError.h"
#include "PropertyResolutionEagerness.h"
#include "PerformanceLevel.h"
#include <map>

namespace GlEngine
{
    namespace ShaderFactory
    {
        class Component;
        class Attribute;
        class PropertySource;

        class ENGINE_SHARED Program
        {
        public:
            Program(PerformanceLevel perforamceLevel = PerformanceLevel::Unset);
            ~Program();

            ShaderFactoryError error = ShaderFactoryError::None;
            ComponentArray<Component*> components;

            void SetPerformanceLevel(PerformanceLevel performanceLevel);
            void SetPropertyResolutionEagerness(PropertyResolutionEagerness eagerness);

            void AddPropertySource(PropertySource *propSource);
            void AddAttribute(Attribute* attribute);

            void ConnectComponentsProperty(ComponentType first, ComponentType last, ShaderProp* prop);

            ShaderSource *Compile();
            void WriteToDisk(std::string name);

        private:
            PerformanceLevel performanceLevel;
            PropertyResolutionEagerness propertyResolutionEagerness;

            void SetDefaultFlags();

            ComponentArray<std::vector<PropertySource*>> resolvedComponents;
            std::vector<Attribute*> attributes;
            std::vector<PropertySource*> propertySources;
            std::vector<PropertySource*> fallbackSources;
            
            std::map<PropertySource*, std::vector<PropertySource*>> propertySourceInputs, propertySourceOutputs;
            std::map<ShaderProp*, PropertySource*> currentPropertySources;
            bool compilationStarted = false;

            size_t AddAttributeInternal(Attribute* attribute, size_t earliest);

            ComponentType latest(std::vector<ComponentType> components);
            ComponentType earliest(std::vector<ComponentType> components);
            std::vector<ComponentType> orderedComponents(PropertySource* source);
            std::map<PropertySource*, std::vector<ComponentType>> sourceConstraints();
            std::set<std::pair<ShaderProp*, PropertySource*>> unresolvedProperties();

            std::vector<PropertySource*> sourceDependencies(PropertySource* source, std::vector<PropertySource*> dependencySources = std::vector<PropertySource*>());
            bool sourceDependenciesMet(PropertySource* source, std::vector<PropertySource*> dependencySources);
            void AddToDependencyTree(PropertySource* source, std::vector<PropertySource*> dependencies);
            void ResolveAttributeDependencies(Attribute* attribute);
            bool TryResolveComponents(std::map<PropertySource*, std::vector<ComponentType>> constraints);
            void ResolveFallbacks();
            void BuildDependencyTree();
        };
    }
}
