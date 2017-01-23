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

            int FindUniform(ShaderProp* prop);
            unsigned FindOrCreateUniform(ShaderProp* prop);

            std::map<PropertySource*, std::vector<PropertySource*>> propertySourceInputs, propertySourceDependents;
            ComponentArray<std::vector<PropertySource*>> componentSources;
            std::map<PropertySource*, ComponentType> sourceComponents;

        private:
            PerformanceLevel performanceLevel;
            PropertyResolutionEagerness propertyResolutionEagerness;

            std::map<size_t, ShaderProp*> uniforms;

            void SetDefaultFlags();

            ComponentArray<std::vector<PropertySource*>> resolvedComponents;
            std::vector<Attribute*> attributes;
            std::vector<PropertySource*> propertySources;
            std::vector<PropertySource*> fallbackSources;
            
            std::vector<PropertySource*> allSources;
            std::map<ShaderProp*, std::vector<PropertySource*>> allPropertySources;
            std::map<ShaderProp*, PropertySource*> currentPropertySources;
            std::map<PropertySource*, std::vector<ComponentType>> constraints;
            bool compilationStarted = false;

            int AddAttributeInternal(Attribute* attribute, int earliest);

            ComponentType latestComponent(std::vector<ComponentType> components);
            ComponentType earliestComponent(std::vector<ComponentType> components);
            std::vector<ComponentType> orderedComponents(PropertySource* source);
            std::map<ShaderProp*, std::set<PropertySource*>> unresolvedProperties();
            std::map<ShaderProp*, std::vector<PropertySource*>> propertyFallbacks();
            bool isEventualChild(PropertySource* parent, PropertySource* child);
            bool isEventualChild(std::set<PropertySource*> parent, std::set<PropertySource*> children);

            std::vector<PropertySource*> sourceDependencies(PropertySource* source, std::vector<PropertySource*> dependencySources = std::vector<PropertySource*>());
            bool SourceDependenciesMet(PropertySource* source, std::vector<PropertySource*> &dependencySources);
            void AddToDependencyTree(PropertySource* source, std::vector<PropertySource*> dependencies);
            
            void AddFallbackToDependencyTree(PropertySource* prop, std::set<PropertySource*> outputs, std::map<PropertySource*, std::vector<ComponentType>> constraints, std::map<PropertySource*, std::vector<ComponentType>> newConstraints);
            void RemoveFallbackFromDependencyTree(PropertySource* prop);
            bool FindFallback(ShaderProp* prop, std::map<ShaderProp*, std::set<PropertySource*>> unresolvedProps, std::map<ShaderProp*, std::vector<PropertySource*>> propFallbacks, std::map<PropertySource*, std::vector<ComponentType>> currentConstraints, std::map<PropertySource*, std::vector<ComponentType>> newConstraints);
            bool ResolveFallbacks();

            void CalculateConstraints();
            void ResolveAttributeDependencies(Attribute* attribute);
            void ResolveComponents();
            void BuildDependencyTree();
        };
    }
}
